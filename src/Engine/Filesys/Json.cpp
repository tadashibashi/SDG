#include "Json.h"
#include "File.h"
#include <Engine/Debug.h>
#include <Engine/Exceptions.h>

namespace SDG
{
    json OpenJson(const Path &path)
    {
        File file;

        if (!file.Open(path))
        {
            throw RuntimeException(String::Format("{}: Failed to open json file: {}", 
                SDG_TRACE, file.GetError()));
        }

        return json::parse(file.Data(), file.Data() + file.Size());
    }
}