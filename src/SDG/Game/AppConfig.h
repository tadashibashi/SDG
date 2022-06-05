//
// Created by Aaron Ishibashi on 4/30/22.
//
#pragma once
#include <SDG/FileSys/XmlLoadable.h>
#include <SDG/Lib/String.h>
#include <cstdint>

namespace SDG
{
    class AppConfig : public XmlLoadable
    {
    public:
        AppConfig() : XmlLoadable("AppConfig"), width(), height(), winFlags(), title(), appName(), orgName() { }

        int width, height;
        uint32_t winFlags;
        String title, appName, orgName;

    private:
        bool LoadImpl(const Xml::XmlDocument &doc) override;
    };
}
