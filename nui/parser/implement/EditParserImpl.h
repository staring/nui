#pragma once

#include "NativeParserImpl.h"


class EditParserImpl : public NativeParserImpl
{
    DECLARE_REFLECTION(TEXT("nui"), TEXT("editparser"))
public:
    EditParserImpl();

    virtual bool IsCorrectObj(nui::Base::NBaseObj* targetObj);
    virtual void FillAttr(nui::Base::NBaseObj* targetObj, nui::Data::NDataReader* styleNode);
};
