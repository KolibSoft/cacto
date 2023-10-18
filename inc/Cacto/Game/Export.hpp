#ifndef CACTO_GAME_EXPORT_HPP
#define CACTO_GAME_EXPORT_HPP

#include <Cacto/Config.hpp>

#ifdef CACTO_GAME_EXPORTS
#define CACTO_GAME_API CACTO_API_EXPORT
#else
#define CACTO_GAME_API CACTO_API_IMPORT
#endif

#endif