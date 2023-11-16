#ifndef CACTO_JSON_VALUE_HPP
#define CACTO_JSON_VALUE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class CACTO_CORE_API JsonValue final
    {

    public:
        enum Kind
        {
            Number,
            String,
            Boolean,
            Null,
            Array,
            Object
        };

        Kind getKind() const;

        const JsonValue &at(szt index) const;
        JsonValue &at(szt index);

        const JsonValue &at(const std::string &key) const;
        JsonValue &at(const std::string &key);

        const f64t &asNumber() const;
        f64t &asNumber();

        const std::string &asString() const;
        std::string &asString();

        const bool &asBoolean() const;
        bool &asBoolean();

        const std::vector<JsonValue> &asArray() const;
        std::vector<JsonValue> &asArray();

        const std::unordered_map<std::string, JsonValue> &asObject() const;
        std::unordered_map<std::string, JsonValue> &asObject();

        bool equals(const JsonValue &other) const;

        JsonValue(f64t number);
        JsonValue(const std::string &string);
        JsonValue(const s8t &string);
        JsonValue(bool boolean);
        JsonValue(std::nullptr_t = 0);
        JsonValue(const std::vector<JsonValue> &array);
        JsonValue(std::initializer_list<JsonValue> array);
        JsonValue(const std::unordered_map<std::string, JsonValue> &object);
        JsonValue(std::initializer_list<std::pair<const std::string, JsonValue>> object);
        virtual ~JsonValue();

        const JsonValue &operator[](szt index) const;
        JsonValue &operator[](szt index);

        const JsonValue &operator[](const std::string &key) const;
        JsonValue &operator[](const std::string &key);

        JsonValue(const JsonValue &other);
        JsonValue &operator=(const JsonValue &other);

        JsonValue(JsonValue &&other);
        JsonValue &operator=(JsonValue &&other);

        bool operator==(const JsonValue &other) const;

        static const JsonValue NumberValue;
        static const JsonValue StringValue;
        static const JsonValue BooleanValue;
        static const JsonValue NullValue;
        static const JsonValue ArrayValue;
        static const JsonValue ObjectValue;

    private:
        void drop();

        Kind m_kind;
        union
        {
            f64t m_number;
            std::string *m_string;
            bool m_boolean;
            std::vector<JsonValue> *m_array;
            std::unordered_map<std::string, JsonValue> *m_object;
        };
    };

}

#endif