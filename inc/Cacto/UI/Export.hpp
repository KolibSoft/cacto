#ifndef CACTO_UI_EXPORT_HPP
#define CACTO_UI_EXPORT_HPP

#include <Cacto/Config.hpp>

#ifdef CACTO_UI_EXPORTS
#define CACTO_UI_API CACTO_API_EXPORT
#else
#define CACTO_UI_API CACTO_API_IMPORT
#endif

#endif