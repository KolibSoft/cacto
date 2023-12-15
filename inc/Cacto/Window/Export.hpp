#pragma once

#include <Cacto/Config.hpp>

#ifdef CACTO_WINDOW_EXPORTS
#define CACTO_WINDOW_API CACTO_API_EXPORT
#else
#define CACTO_WINDOW_API CACTO_API_IMPORT
#endif
