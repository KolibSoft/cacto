#ifndef CACTO_PHYSICS_EXPORT_HPP
#define CACTO_PHYSICS_EXPORT_HPP

#include <Cacto/Config.hpp>

#ifdef CACTO_PHYSICS_EXPORTS
#define CACTO_PHYSICS_API CACTO_API_EXPORT
#else
#define CACTO_PHYSICS_API CACTO_API_IMPORT
#endif

#endif