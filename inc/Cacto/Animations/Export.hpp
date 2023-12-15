#pragma once

#include <Cacto/Config.hpp>

#ifdef CACTO_ANIMATIONS_EXPORTS
#define CACTO_ANIMATIONS_API CACTO_API_EXPORT
#else
#define CACTO_ANIMATIONS_API CACTO_API_IMPORT
#endif
