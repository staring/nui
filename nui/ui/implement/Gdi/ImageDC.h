#pragma once




class ImageDC
{
    ImageDC(const ImageDC&);
    ImageDC& operator = (const ImageDC&);
public:
    ImageDC(HDC hDc, HBITMAP bitmap)
    {
        bool nullDc = (hDc == NULL);
        if(nullDc)
            hDc = ::GetDC(NULL);
        memDC_ = ::CreateCompatibleDC(hDc);
        oldBitmap_ = ::SelectObject(memDC_, bitmap);
        ::SetStretchBltMode(memDC_, COLORONCOLOR);
        if(nullDc)
            ::ReleaseDC(NULL, hDc);
        NAssertError(oldBitmap_ != NULL, _T("Error in ImageDC::ImageDC"));
    }
    ~ImageDC()
    {
        if(memDC_ != NULL)
        {
            if(oldBitmap_ != NULL)
                ::SelectObject(memDC_, oldBitmap_);
            oldBitmap_ = NULL;
            ::DeleteDC(memDC_);
            memDC_ = NULL;
        }
    }

    operator HDC()
    {
        return memDC_;
    }

private:
    HDC memDC_;
    HGDIOBJ oldBitmap_;
};
