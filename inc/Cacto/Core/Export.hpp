#pragma once

#include <Cacto/Config.hpp>

#ifdef CACTO_CORE_EXPORTS
#define CACTO_CORE_API CACTO_API_EXPORT
#else
#define CACTO_CORE_API CACTO_API_IMPORT
#endif
