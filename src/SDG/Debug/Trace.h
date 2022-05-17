#pragma once
#include <string>

/// Creates a string with information to trace back to the current file/line.
#define SDG_TRACE() (std::string(__FILE__) + ":" + std::to_string(__LINE__) +\
    ": " + std::string(__func__) + ": ")
