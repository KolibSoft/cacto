#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Lang/Printable.hpp>
#include <Cacto/Lang/Scannable.hpp>

namespace cacto
{

    class Printer;
    class Scanner;

    class CACTO_LANG_API JsonValue final
        : public virtual Printable,
          public virtual Scannable
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

        bool isNumber() const;
        f64t getNumber(f64t def = 0) const;
        void setNumber(f64t value);
        explicit operator f64t() const;

        bool isString() const;
        std::string getString(const std::string &def = "") const;
        void setString(const std::string &value);
        explicit operator std::string() const;

        const std::string &asString() const;
        std::string &asString();

        bool isBoolean() const;
        bool getBoolean(bool def = false) const;
        void setBoolean(bool value);
        explicit operator bool() const;

        bool isArray() const;
        std::vector<JsonValue> getArray(const std::vector<JsonValue> &def = {}) const;
        void setArray(const std::vector<JsonValue> &value);
        explicit operator std::vector<JsonValue>() const;

        void append(const JsonValue &value);
        void resize(szt count);

        const std::vector<JsonValue> &asArray() const;
        std::vector<JsonValue> &asArray();
        const JsonValue &operator[](szt index) const;
        JsonValue &operator[](szt index);

        bool isObject() const;
        std::unordered_map<std::string, JsonValue> getObject(const std::unordered_map<std::string, JsonValue> &def = {}) const;
        void setObject(const std::unordered_map<std::string, JsonValue> &value);
        explicit operator std::unordered_map<std::string, JsonValue>() const;

        const std::unordered_map<std::string, JsonValue> &asObject() const;
        std::unordered_map<std::string, JsonValue> &asObject();
        const JsonValue &operator[](const std::string &key) const;
        JsonValue &operator[](const std::string &key);

        void print(Printer &printer) const override;
        bool scan(Scanner &scanner) override;

        JsonValue(f64t number);
        JsonValue(f32t number);
        JsonValue(i64t number);
        JsonValue(i32t number);
        JsonValue(const std::string &string);
        JsonValue(const s8t &string);
        JsonValue(bool boolean);
        JsonValue(std::nullptr_t = 0);
        JsonValue(const std::vector<JsonValue> &array);
        JsonValue(std::initializer_list<JsonValue> array);
        JsonValue(const std::unordered_map<std::string, JsonValue> &object);
        JsonValue(std::initializer_list<std::pair<const std::string, JsonValue>> object);
        virtual ~JsonValue();

        JsonValue(const JsonValue &other);
        JsonValue &operator=(const JsonValue &other);

        JsonValue(JsonValue &&other);
        JsonValue &operator=(JsonValue &&other);

        bool operator==(const JsonValue &other) const;
        bool operator!=(const JsonValue &other) const;

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
