#pragma once

// Use the spdlog static lib only
#ifdef SPDLOG_HEADER_ONLY
#undef SPDLOG_HEADER_ONLY
#endif
#include <spdlog/logger.h>
