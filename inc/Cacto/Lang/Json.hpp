#ifndef CACTO_JSON_HPP
#define CACTO_JSON_HPP

#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class JsonValue;

    class CACTO_LANG_API Json
    {

    public:
        virtual JsonValue toJson() const = 0;
        virtual void fromJson(const JsonValue &json) = 0;

        void toFile(const std::filesystem::path &path) const;
        void fromFile(const std::filesystem::path &path);

        Json() = default;
        virtual ~Json() = default;
    };

}

#endif