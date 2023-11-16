#ifndef CACTO_LANG_EXPORT_HPP
#define CACTO_LANG_EXPORT_HPP

#include <Cacto/Config.hpp>

#ifdef CACTO_LANG_EXPORTS
#define CACTO_LANG_API CACTO_API_EXPORT
#else
#define CACTO_LANG_API CACTO_API_IMPORT
#endif

#endif