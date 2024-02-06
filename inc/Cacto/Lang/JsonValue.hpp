#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Lang/Printable.hpp>
#include <Cacto/Lang/Scannable.hpp>

namespace cacto
{

    enum class JsonType
    {
        Null,
        Number,
        String,
        Boolean,
        Array,
        Object
    };

    class JsonValue;

    using JsonNumber = f64t;
    using JsonString = std::string;
    using JsonBoolean = bool;
    using JsonNull = std::nullptr_t;
    using JsonArray = std::vector<JsonValue>;
    using JsonObject = std::unordered_map<JsonString, JsonValue>;

    class Printer;
    class Scanner;

    class CACTO_LANG_API JsonValue final
        : public virtual Printable,
          public virtual Scannable
    {

    public:
        JsonType getType() const;
        inline bool isNull() const;

        inline bool isNumber() const;
        JsonNumber getNumber(JsonNumber def = 0) const;
        void setNumber(JsonNumber value = 0);
        inline explicit operator JsonNumber() const;

        inline bool isString() const;
        JsonString getString(const JsonString &def = "") const;
        void setString(const JsonString &value = "");
        inline explicit operator JsonString() const;

        const JsonString &asString() const;
        JsonString &asString();

        inline bool isBoolean() const;
        JsonBoolean getBoolean(JsonBoolean def = false) const;
        void setBoolean(JsonBoolean value = false);
        inline explicit operator JsonBoolean() const;

        inline bool isArray() const;
        JsonArray getArray(const JsonArray &def = {}) const;
        void setArray(const JsonArray &value = {});
        inline explicit operator JsonArray() const;

        void append(const JsonValue &value);
        void resize(szt count);
        const JsonValue &operator[](szt index) const;
        JsonValue &operator[](szt index);

        const JsonArray &asArray() const;
        JsonArray &asArray();

        inline bool isObject() const;
        JsonObject getObject(const JsonObject &def = {}) const;
        void setObject(const JsonObject &value = {});
        inline explicit operator JsonObject() const;

        const JsonValue &operator[](const JsonString &key) const;
        JsonValue &operator[](const JsonString &key);

        const JsonObject &asObject() const;
        JsonObject &asObject();

        void print(Printer &printer) const override;
        bool scan(Scanner &scanner) override;

        JsonValue(JsonNumber number);
        JsonValue(f32t number);
        JsonValue(i64t number);
        JsonValue(i32t number);
        JsonValue(const JsonString &string);
        JsonValue(const s8t &string);
        JsonValue(JsonBoolean boolean);
        JsonValue(JsonNull = 0);
        JsonValue(const JsonArray &array);
        JsonValue(std::initializer_list<JsonValue> array);
        JsonValue(const JsonObject &object);
        JsonValue(std::initializer_list<std::pair<const JsonString, JsonValue>> object);
        virtual ~JsonValue();

        JsonValue(const JsonValue &other);
        JsonValue &operator=(const JsonValue &other);

        JsonValue(JsonValue &&other);
        JsonValue &operator=(JsonValue &&other);

        bool operator==(const JsonValue &other) const;
        bool operator!=(const JsonValue &other) const;

        static const JsonValue Null;
        static const JsonString EmptyString;
        static const JsonArray EmptyArray;
        static const JsonObject EmptyObject;

    private:
        void drop();

        JsonType m_type;
        union
        {
            JsonNumber m_number;
            JsonString *m_string;
            JsonBoolean m_boolean;
            JsonArray *m_array;
            JsonObject *m_object;
        };
    };

}

#include <Cacto/Lang/JsonValue.inl>