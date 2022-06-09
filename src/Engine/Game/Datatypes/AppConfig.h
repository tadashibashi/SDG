//
// Created by Aaron Ishibashi on 4/30/22.
//
#pragma once
#include <Engine/FileSys/Xml/XmlLoadable.h>
#include <Engine/Lib/String.h>
#include <cstdint>

namespace SDG
{
    class AppConfig : public XmlLoadable
    {
    public:
        AppConfig() : XmlLoadable("AppConfig"), width(), height(), winFlags(), title(), appName(), orgName() { }
        AppConfig(int width, int height, uint32_t winFlags, const String &title, const String &appName, const String &orgName) : 
            XmlLoadable("AppConfig"), width(width), height(height), winFlags(winFlags), title(title), appName(appName), orgName(orgName) { }

        int width, height;
        uint32_t winFlags;
        String title, appName, orgName;

    private:
        bool LoadImpl(const Xml::XmlDocument &doc) override;
    };
}
