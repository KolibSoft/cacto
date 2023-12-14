#pragma once

#include <Cacto/Config.hpp>

#ifdef CACTO_GRAPHICS_EXPORTS
#define CACTO_GRAPHICS_API CACTO_API_EXPORT
#else
#define CACTO_GRAPHICS_API CACTO_API_IMPORT
#endif
