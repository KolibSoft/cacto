#include <stdexcept>
#include <fstream>
#include <Cacto/Lang/JsonPrinter.hpp>
#include <Cacto/Lang/JsonScanner.hpp>
#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    JsonType JsonValue::getType() const
    {
        return m_type;
    }

    bool JsonValue::isNull() const
    {
        return m_type == JsonType::Null;
    }

    bool JsonValue::isNumber() const
    {
        return m_type == JsonType::Number;
    }

    JsonNumber JsonValue::getNumber(JsonNumber def) const
    {
        if (m_type != JsonType::Number)
            return def;
        return m_number;
    }

    void JsonValue::setNumber(JsonNumber value)
    {
        if (m_type == JsonType::Number)
            m_number = value;
        else
        {
            drop();
            m_type = JsonType::Number;
            m_number = value;
        }
    }

    JsonValue::operator JsonNumber() const
    {
        return getNumber();
    }

    bool JsonValue::isString() const
    {
        return m_type == JsonType::String;
    }

    JsonString JsonValue::getString(const JsonString &def) const
    {
        if (m_type != JsonType::String)
            return def;
        return *m_string;
    }

    void JsonValue::setString(const JsonString &value)
    {
        if (m_type == JsonType::String)
            *m_string = value;
        else
        {
            drop();
            m_type = JsonType::String;
            m_string = new JsonString(value);
        }
    }

    const JsonString &JsonValue::asString() const
    {
        if (m_type != JsonType::String)
            return EmptyString;
        return *m_string;
    }

    JsonString &JsonValue::asString()
    {
        if (m_type != JsonType::String)
            throw std::runtime_error("Json is not a string value");
        return *m_string;
    }

    JsonValue::operator std::string() const
    {
        return getString();
    }

    bool JsonValue::isBoolean() const
    {
        return m_type == JsonType::Boolean;
    }

    JsonBoolean JsonValue::getBoolean(JsonBoolean def) const
    {
        if (m_type != JsonType::Boolean)
            return def;
        return m_boolean;
    }

    void JsonValue::setBoolean(JsonBoolean value)
    {
        if (m_type == JsonType::Boolean)
            m_boolean = value;
        else
        {
            drop();
            m_type = JsonType::Boolean;
            m_boolean = value;
        }
    }

    JsonValue::operator JsonBoolean() const
    {
        return getBoolean();
    }

    bool JsonValue::isArray() const
    {
        return m_type == JsonType::Array;
    }

    JsonArray JsonValue::getArray(const JsonArray &def) const
    {
        if (m_type != JsonType::Array)
            return def;
        return *m_array;
    }

    void JsonValue::setArray(const JsonArray &value)
    {
        if (m_type == JsonType::Array)
            *m_array = value;
        else
        {
            drop();
            m_type = JsonType::Array;
            m_array = new JsonArray(value);
        }
    }

    JsonValue::operator JsonArray() const
    {
        return getArray();
    }

    void JsonValue::append(const JsonValue &value)
    {
        if (m_type != JsonType::Array)
            throw std::runtime_error("Json is not an array value");
        m_array->push_back(value);
    }

    void JsonValue::resize(szt count)
    {
        if (m_type != JsonType::Array)
            throw std::runtime_error("Json is not an array value");
        m_array->resize(count);
    }

    const JsonValue &JsonValue::operator[](szt index) const
    {
        if (m_type != JsonType::Array)
            return Null;
        if (index >= m_array->size())
            return Null;
        return m_array->at(index);
    }

    JsonValue &JsonValue::operator[](szt index)
    {
        if (m_type != JsonType::Array)
            throw std::runtime_error("Json is not an array value");
        return m_array->operator[](index);
    }

    const JsonArray &JsonValue::asArray() const
    {
        if (m_type != JsonType::Array)
            return EmptyArray;
        return *m_array;
    }

    JsonArray &JsonValue::asArray()
    {
        if (m_type != JsonType::Array)
            throw std::runtime_error("Json is not an array value");
        return *m_array;
    }

    bool JsonValue::isObject() const
    {
        return m_type == JsonType::Object;
    }

    JsonObject JsonValue::getObject(const JsonObject &def) const
    {
        if (m_type != JsonType::Object)
            return def;
        return *m_object;
    }

    void JsonValue::setObject(const JsonObject &value)
    {
        if (m_type == JsonType::Object)
            *m_object = value;
        else
        {
            drop();
            m_type = JsonType::Object;
            m_object = new JsonObject(value);
        }
    }

    JsonValue::operator JsonObject() const
    {
        return getObject();
    }

    const JsonValue &JsonValue::operator[](const JsonString &key) const
    {
        if (m_type != JsonType::Object)
            return Null;
        for (auto &pair : *m_object)
            if (pair.first == key)
                return pair.second;
        return Null;
    }

    JsonValue &JsonValue::operator[](const JsonString &key)
    {
        if (m_type != JsonType::Object)
            throw std::runtime_error("Json is not an object value");
        return m_object->operator[](key);
    }

    const JsonObject &JsonValue::asObject() const
    {
        if (m_type != JsonType::Object)
            return EmptyObject;
        return *m_object;
    }

    JsonObject &JsonValue::asObject()
    {
        if (m_type != JsonType::Object)
            throw std::runtime_error("Json is not an object value");
        return *m_object;
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

    JsonValue::JsonValue(JsonNumber number)
        : m_type(JsonType::Number),
          m_number(number)
    {
    }

    JsonValue::JsonValue(f32t number)
        : m_type(JsonType::Number),
          m_number(number)
    {
    }
    JsonValue::JsonValue(i64t number)
        : m_type(JsonType::Number),
          m_number(number)
    {
    }
    JsonValue::JsonValue(i32t number)
        : m_type(JsonType::Number),
          m_number(number)
    {
    }

    JsonValue::JsonValue(const JsonString &string)
        : m_type(JsonType::String),
          m_string(new JsonString(string))
    {
    }

    JsonValue::JsonValue(const s8t &string)
        : m_type(JsonType::String),
          m_string(new JsonString(string))
    {
    }

    JsonValue::JsonValue(JsonBoolean boolean)
        : m_type(JsonType::Boolean),
          m_boolean(boolean)
    {
    }

    JsonValue::JsonValue(JsonNull)
        : m_type(JsonType::Null),
          m_number(0)
    {
    }

    JsonValue::JsonValue(const JsonArray &array)
        : m_type(JsonType::Array),
          m_array(new JsonArray(array))
    {
    }

    JsonValue::JsonValue(std::initializer_list<JsonValue> array)
        : m_type(JsonType::Array),
          m_array(new JsonArray(array))
    {
    }

    JsonValue::JsonValue(const JsonObject &object)
        : m_type(JsonType::Object),
          m_object(new JsonObject(object))
    {
    }

    JsonValue::JsonValue(std::initializer_list<std::pair<const JsonString, JsonValue>> object)
        : m_type(JsonType::Object),
          m_object(new JsonObject(object))
    {
    }

    JsonValue::~JsonValue()
    {
        drop();
    }

    JsonValue::JsonValue(const JsonValue &other)
        : m_type(other.m_type)
    {
        switch (m_type)
        {
        case JsonType::Number:
            m_number = other.m_number;
            break;
        case JsonType::String:
            m_string = new JsonString(*other.m_string);
            break;
        case JsonType::Boolean:
            m_boolean = other.m_boolean;
            break;
        case JsonType::Null:
            m_number = 0;
            break;
        case JsonType::Array:
            m_array = new JsonArray(*other.m_array);
            break;
        case JsonType::Object:
            m_object = new JsonObject(*other.m_object);
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
        m_type = other.m_type;
        switch (m_type)
        {
        case JsonType::Number:
            m_number = other.m_number;
            break;
        case JsonType::String:
            m_string = other.m_string;
            break;
        case JsonType::Boolean:
            m_boolean = other.m_boolean;
            break;
        case JsonType::Null:
            m_number = 0;
            break;
        case JsonType::Array:
            m_array = other.m_array;
            break;
        case JsonType::Object:
            m_object = other.m_object;
            break;
        }
        other.m_type = JsonType::Null;
        other.m_number = 0;
        return *this;
    }

    bool JsonValue::operator==(const JsonValue &other) const
    {
        if (m_type == other.m_type)
            switch (m_type)
            {
            case JsonType::Number:
                return m_number == other.m_number;
            case JsonType::String:
                return *m_string == *other.m_string;
            case JsonType::Boolean:
                return m_boolean == other.m_boolean;
            case JsonType::Null:
                return true;
            case JsonType::Array:
                return *m_array == *other.m_array;
            case JsonType::Object:
                return *m_object == *other.m_object;
            }
        return false;
    }

    bool JsonValue::operator!=(const JsonValue &other) const
    {
        return !(*this == other);
    }

    const JsonValue JsonValue::Null = nullptr;
    const JsonString JsonValue::EmptyString{};
    const JsonArray JsonValue::EmptyArray{};
    const JsonObject JsonValue::EmptyObject{};

    void JsonValue::drop()
    {
        switch (m_type)
        {
        case JsonType::String:
            delete m_string;
            break;
        case JsonType::Array:
            delete m_array;
            break;
        case JsonType::Object:
            delete m_object;
            break;
        default:
            break;
        }
        m_type = JsonType::Null;
        m_number = 0;
    }

}