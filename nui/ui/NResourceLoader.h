#pragma once



#include "../base/BaseObj.h"
#include "NImage.h"
#include "NShape.h"
#include "NText.h"

namespace nui
{
    namespace Ui
    {
        class NUI_INTF NResourceLoader : public Base::NBaseObj
        {
        public:
            virtual NImage* LoadImage(LPCTSTR filePath) = 0;
            virtual NShape* CreateShape() = 0;
            virtual NText* CreateText(LPCTSTR text) = 0;
        };
    }
}