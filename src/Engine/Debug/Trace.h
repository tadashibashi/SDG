#pragma once
#include <Engine/Platform.h>
#if SDG_TARGET_WINDOWS
#define SDG_FILESLASH '\\'
#else
#define SDG_FILESLASH '/'
#endif

#include <Engine/Lib/StringView.h>
#define SDG_LINE SDG::ToString(__LINE__)
#define SDG_FUNC SDG::String(__func__)
#define SDG_FILEPATH SDG::String(__FILE__)

#define SDG_FILENAME SDG::String(SDG::StringView(__FILE__).Substr(\
SDG::StringView(__FILE__).FindLastOf(SDG_FILESLASH) == SDG::StringView::NullPos ?\
0 : SDG::StringView(__FILE__).FindLastOf(SDG_FILESLASH) + 1 ))

#define SDG_TRACE SDG::String::Format("{}:{}: {}", __FILE__, __LINE__, __func__)
