#include "stdafx.h"
#include "../NAssert.h"

using namespace NUI;
using namespace Base;

#if defined(_DEBUG) || defined(_ENABLE_NASSERT_)

namespace
{
    bool g_AssertEnabled = true;
    struct stAssertProcData
    {
        LPCTSTR szMsg;
        LPCTSTR szTitle;
        int     nResult;
    };
    DWORD CALLBACK AssertThreadProc(void* pParam)
    {
        stAssertProcData* pData = (stAssertProcData*)pParam;
        pData->nResult = ::MessageBox(NULL, pData->szMsg, pData->szTitle, MB_ICONERROR | MB_ABORTRETRYIGNORE);
        return 0;
    }
}

NUI_API void NAssertImpl(LPCTSTR filePath, int line, LPCTSTR format, ...)
{
    if(!g_AssertEnabled)
        return;

    NString strMsg;
    NString strFormat;
    NString strParams;

    va_list args;
    va_start(args, format);

    strParams = strParams.Format(format, &args);

    strFormat =
        _T("Assertion Failed��\r\n\r\n")
        _T("File: %1\r\n")
        _T("Line: %2\r\n")
        _T("Message: %3\r\n\r\n");

    strMsg = strFormat.arg(filePath).arg(line).arg(strParams);

    // when the process is terminating, the MessageBox will be ended auto
    //  so use tickCount to detect this.
    DWORD dwTickCount = ::GetTickCount();

    int nResult = IDRETRY;
    {
        stAssertProcData data;
        data.szMsg = strMsg.GetData();
        data.szTitle = _T("Assertion Failed");
        data.nResult = IDRETRY;
        HANDLE hThread = ::CreateThread(0, 0, &AssertThreadProc, (void*)&data, 0, 0);
        ::WaitForSingleObject(hThread, INFINITE);
        ::CloseHandle(hThread);
        nResult = data.nResult;
    }

    dwTickCount = ::GetTickCount() - dwTickCount;
    if((::GetLastError() == ERROR_INVALID_HANDLE || dwTickCount < 500)
        && nResult == IDABORT)
    {
        nResult = IDRETRY;
    }
    if(nResult == IDABORT)
    {
        ExitProcess(1);
    }
    else if(nResult == IDRETRY)
    {
        if(IsDebuggerPresent())
        {
            DebugBreak();
        }
        else
        {
            for(int i=0; i<10; ++ i)
            {
                MessageBeep(-1);
                Sleep(10);
            }
            DebugBreak();
        }
    }
    else if(nResult == IDIGNORE)
    {
        ;
    }
}

NUI_API bool NAssertEnableImpl(bool enable)
{
    bool result = g_AssertEnabled;
    g_AssertEnabled = enable;
    return result;
}

#endif
