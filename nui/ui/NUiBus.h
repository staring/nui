#pragma once


#include "NRenderDef.h"


namespace nui
{
    namespace Ui
    {
        class NUI_INTF NRender;
        class NUI_INTF NResourceLoader;

        class NUI_CLASS NUiBus
        {
            NUiBus();
            NUiBus(const NUiBus&);
            NUiBus& operator = (const NUiBus&);
        public:
            ~NUiBus();
            void Init(NRenderType::Type type);
            void Destroy();

            static NUiBus& Instance();

            NRender* CreateRender();
            NResourceLoader* GetResourceLoader();

        private:
            NRenderType::Type renderType_;
            NResourceLoader* loader_;
        };
    }
}
