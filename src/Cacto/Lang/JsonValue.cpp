#include <stdexcept>
#include <fstream>
#include <Cacto/Lang/JsonPrinter.hpp>
#include <Cacto/Lang/JsonScanner.hpp>
#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    JsonValue::Kind JsonValue::getKind() const
    {
        return m_kind;
    }

    bool JsonValue::isNumber() const
    {
        return m_kind == Number;
    }

    f64t JsonValue::getNumber(f64t def) const
    {
        if (m_kind != Number)
            return def;
        return m_number;
    }

    void JsonValue::setNumber(f64t value)
    {
        if (m_kind == Number)
            m_number = value;
        else
        {
            drop();
            m_kind = Number;
            m_number = value;
        }
    }

    JsonValue::operator f64t() const
    {
        return getNumber();
    }

    bool JsonValue::isString() const
    {
        return m_kind == String;
    }

    std::string JsonValue::getString(const std::string &def) const
    {
        if (m_kind != String)
            return def;
        return *m_string;
    }

    void JsonValue::setString(const std::string &value)
    {
        if (m_kind == String)
            *m_string = value;
        else
        {
            drop();
            m_kind = String;
            m_string = new std::string(value);
        }
    }

    const std::string &JsonValue::asString() const
    {
        if (m_kind != String)
            throw std::runtime_error("Json is not a string value");
        return *m_string;
    }

    std::string &JsonValue::asString()
    {
        if (m_kind != String)
            throw std::runtime_error("Json is not a string value");
        return *m_string;
    }

    JsonValue::operator std::string() const
    {
        return getString();
    }

    bool JsonValue::isBoolean() const
    {
        return m_kind == Boolean;
    }

    bool JsonValue::getBoolean(bool def) const
    {
        if (m_kind != Boolean)
            return def;
        return m_boolean;
    }

    void JsonValue::setBoolean(bool value)
    {
        if (m_kind == Boolean)
            m_boolean = value;
        else
        {
            drop();
            m_kind = Boolean;
            m_boolean = value;
        }
    }

    JsonValue::operator bool() const
    {
        return getBoolean();
    }

    bool JsonValue::isArray() const
    {
        return m_kind == Array;
    }

    std::vector<JsonValue> JsonValue::getArray(const std::vector<JsonValue> &def) const
    {
        if (m_kind != Array)
            return def;
        return *m_array;
    }

    void JsonValue::setArray(const std::vector<JsonValue> &value)
    {
        if (m_kind == Array)
            *m_array = value;
        else
        {
            drop();
            m_kind = Array;
            m_array = new std::vector<JsonValue>(value);
        }
    }

    JsonValue::operator std::vector<JsonValue>() const
    {
        return getArray();
    }

    void JsonValue::append(const JsonValue &value)
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        m_array->push_back(value);
    }

    const std::vector<JsonValue> &JsonValue::asArray() const
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        return *m_array;
    }

    std::vector<JsonValue> &JsonValue::asArray()
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        return *m_array;
    }

    const JsonValue &JsonValue::operator[](szt index) const
    {
        if (m_kind != Array)
            return NullValue;
        if (index >= m_array->size())
            return NullValue;
        return m_array->at(index);
    }

    JsonValue &JsonValue::operator[](szt index)
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        return m_array->operator[](index);
    }

    bool JsonValue::isObject() const
    {
        return m_kind == Object;
    }

    std::unordered_map<std::string, JsonValue> JsonValue::getObject(const std::unordered_map<std::string, JsonValue> &def) const
    {
        if (m_kind != Object)
            return def;
        return *m_object;
    }

    void JsonValue::setObject(const std::unordered_map<std::string, JsonValue> &value)
    {
        if (m_kind == Object)
            *m_object = value;
        else
        {
            drop();
            m_kind = Object;
            m_object = new std::unordered_map<std::string, JsonValue>(value);
        }
    }

    JsonValue::operator std::unordered_map<std::string, JsonValue>() const
    {
        return getObject();
    }

    const std::unordered_map<std::string, JsonValue> &JsonValue::asObject() const
    {
        if (m_kind != Object)
            throw std::runtime_error("Json is not an object value");
        return *m_object;
    }

    std::unordered_map<std::string, JsonValue> &JsonValue::asObject()
    {
        if (m_kind != Object)
            throw std::runtime_error("Json is not an object value");
        return *m_object;
    }

    const JsonValue &JsonValue::operator[](const std::string &key) const
    {
        if (m_kind != Object)
            return NullValue;
        for (auto &pair : *m_object)
            if (pair.first == key)
                return pair.second;
        return NullValue;
    }

    JsonValue &JsonValue::operator[](const std::string &key)
    {
        if (m_kind != Object)
            throw std::runtime_error("Json is not an object value");
        return m_object->operator[](key);
    }

    void JsonValue::print(Printer &printer) const
    {
        JsonPrinter jprinter{printer};
        jprinter.printJson(*this);
    }

    bool JsonValue::scan(Scanner &scanner)
    {
        JsonScanner jscanner{scanner};
        auto success = jscanner.scanJson(*this);
        return success;
    }

    JsonValue::JsonValue(f64t number)
        : m_kind(Number),
          m_number(number)
    {
    }

    JsonValue::JsonValue(f32t number)
        : m_kind(Number),
          m_number(number)
    {
    }
    JsonValue::JsonValue(i64t number)
        : m_kind(Number),
          m_number(number)
    {
    }
    JsonValue::JsonValue(i32t number)
        : m_kind(Number),
          m_number(number)
    {
    }

    JsonValue::JsonValue(const std::string &string)
        : m_kind(String),
          m_string(new std::string(string))
    {
    }

    JsonValue::JsonValue(const s8t &string)
        : m_kind(String),
          m_string(new std::string(string))
    {
    }

    JsonValue::JsonValue(bool boolean)
        : m_kind(Boolean),
          m_boolean(boolean)
    {
    }

    JsonValue::JsonValue(std::nullptr_t)
        : m_kind(Null),
          m_number(0)
    {
    }

    JsonValue::JsonValue(const std::vector<JsonValue> &array)
        : m_kind(Array),
          m_array(new std::vector<JsonValue>(array))
    {
    }

    JsonValue::JsonValue(std::initializer_list<JsonValue> array)
        : m_kind(Array),
          m_array(new std::vector<JsonValue>(array))
    {
    }

    JsonValue::JsonValue(const std::unordered_map<std::string, JsonValue> &object)
        : m_kind(Object),
          m_object(new std::unordered_map<std::string, JsonValue>(object))
    {
    }

    JsonValue::JsonValue(std::initializer_list<std::pair<const std::string, JsonValue>> object)
        : m_kind(Object),
          m_object(new std::unordered_map<std::string, JsonValue>(object))
    {
    }

    JsonValue::~JsonValue()
    {
        drop();
    }

    JsonValue::JsonValue(const JsonValue &other)
        : m_kind(other.m_kind)
    {
        switch (m_kind)
        {
        case Number:
            m_number = other.m_number;
            break;
        case String:
            m_string = new std::string(*other.m_string);
            break;
        case Boolean:
            m_boolean = other.m_boolean;
            break;
        case Null:
            m_number = 0;
            break;
        case Array:
            m_array = new std::vector<JsonValue>(*other.m_array);
            break;
        case Object:
            m_object = new std::unordered_map<std::string, JsonValue>(*other.m_object);
            break;
        }
    }

    JsonValue &JsonValue::operator=(const JsonValue &other)
    {
        auto copy = JsonValue(other);
        *this = std::move(copy);
        return *this;
    }

    JsonValue::JsonValue(JsonValue &&other)
        : JsonValue(nullptr)
    {
        *this = std::move(other);
    }

    JsonValue &JsonValue::operator=(JsonValue &&other)
    {
        drop();
        m_kind = other.m_kind;
        switch (m_kind)
        {
        case Number:
            m_number = other.m_number;
            break;
        case String:
            m_string = other.m_string;
            break;
        case Boolean:
            m_boolean = other.m_boolean;
            break;
        case Null:
            m_number = 0;
            break;
        case Array:
            m_array = other.m_array;
            break;
        case Object:
            m_object = other.m_object;
            break;
        }
        other.m_kind = Null;
        other.m_number = 0;
        return *this;
    }

    bool JsonValue::operator==(const JsonValue &other) const
    {
        if (m_kind == other.m_kind)
            switch (m_kind)
            {
            case Number:
                return m_number == other.m_number;
            case String:
                return *m_string == *other.m_string;
            case Boolean:
                return m_boolean == other.m_boolean;
            case Null:
                return true;
            case Array:
                return *m_array == *other.m_array;
            case Object:
                return *m_object == *other.m_object;
            }
        return false;
    }

    bool JsonValue::operator!=(const JsonValue &other) const
    {
        return !(*this == other);
    }

    const JsonValue JsonValue::NumberValue = 0.0;
    const JsonValue JsonValue::StringValue = std::string();
    const JsonValue JsonValue::BooleanValue = false;
    const JsonValue JsonValue::NullValue = nullptr;
    const JsonValue JsonValue::ArrayValue = std::vector<JsonValue>();
    const JsonValue JsonValue::ObjectValue = std::unordered_map<std::string, JsonValue>();

    void JsonValue::drop()
    {
        switch (m_kind)
        {
        case String:
            delete m_string;
            break;
        case Array:
            delete m_array;
            break;
        case Object:
            delete m_object;
            break;
        default:
            break;
        }
        m_kind = Null;
        m_number = 0;
    }

}