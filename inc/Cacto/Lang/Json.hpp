#ifndef CACTO_JSON_HPP
#define CACTO_JSON_HPP

#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

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