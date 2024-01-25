#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <ostream>
#include <istream>
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
        const f64t &asNumber() const;
        f64t &asNumber();

        bool isString() const;
        std::string getString(const std::string &def = "") const;
        const std::string &asString() const;
        std::string &asString();

        bool isBoolean() const;
        bool getBoolean(bool def = false) const;
        const bool &asBoolean() const;
        bool &asBoolean();

        bool isArray() const;
        const std::vector<JsonValue> &asArray() const;
        std::vector<JsonValue> &asArray();
        const JsonValue &operator[](szt index) const;
        JsonValue &operator[](szt index);

        bool isObject() const;
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
