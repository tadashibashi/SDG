#pragma once
#if CI
# include <spdlog/fmt/bundled/format.h>
#else
# include <spdlog/fmt/bundled/core.h>
#ifndef FMT_STRING
# define FMT_STRING(s) s
#endif
#endif
