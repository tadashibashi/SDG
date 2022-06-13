#pragma once
#include "TmxObject.h"
#include <Engine/Lib/String.h>

namespace SDG::Tiled
{
    class Export : public TmxObject
    {
    public:
        Export() : TmxObject("export") { }

        const String &Target() const { return target; }
        const String &Format() const { return format; }

    private:
        void LoadImpl(const Xml::XmlElement &el) override;
        String target, format;
    };
}
