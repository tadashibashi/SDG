#pragma once
#include <Engine/Filesys/Path.h>

#include <nlohmann/json.hpp>

namespace SDG
{
    using json = nlohmann::json;

    json OpenJson(const Path &path);
}
