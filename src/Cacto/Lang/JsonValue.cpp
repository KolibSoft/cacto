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

    const JsonValue &JsonValue::at(szt index) const
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        return m_array->at(index);
    }

    JsonValue &JsonValue::at(szt index)
    {
        if (m_kind != Array)
            throw std::runtime_error("Json is not an array value");
        return m_array->at(index);
    }

    const JsonValue &JsonValue::at(const std::string &key) const
    {
        if (m_kind != Object)
            throw std::runtime_error("Json is not an object value");
        return m_object->operator[](key);
    }

    JsonValue &JsonValue::at(const std::string &key)
    {
        if (m_kind != Object)
            throw std::runtime_error("Json is not an object value");
        return m_object->operator[](key);
    }

    const f64t &JsonValue::asNumber() const
    {
        if (m_kind != Number)
            throw std::runtime_error("Json is not an number value");
        return m_number;
    }

    f64t &JsonValue::asNumber()
    {
        if (m_kind != Number)
            throw std::runtime_error("Json is not an number value");
        return m_number;
    }

    const std::string &JsonValue::asString() const
    {
        if (m_kind != String)
            throw std::runtime_error("Json is not an string value");
        return *m_string;
    }

    std::string &JsonValue::asString()
    {
        if (m_kind != String)
            throw std::runtime_error("Json is not an string value");
        return *m_string;
    }

    const bool &JsonValue::asBoolean() const
    {
        if (m_kind != Boolean)
            throw std::runtime_error("Json is not an boolean value");
        return m_boolean;
    }

    bool &JsonValue::asBoolean()
    {
        if (m_kind != Boolean)
            throw std::runtime_error("Json is not an boolean value");
        return m_boolean;
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

    void JsonValue::print(JsonPrinter &printer) const
    {
        switch (m_kind)
        {
        case Number:
            printer.printNumber(m_number);
            break;
        case String:
            printer.printString(*m_string);
            break;
        case Boolean:
            printer.printBoolean(m_boolean);
            break;
        case Null:
            printer.printNull();
            break;
        case Array:
            printer.print("[");
            if (m_array->size() > 0)
            {
                if (printer.getIdentation() > 0)
                {
                    printer.ident();
                    printer.println();
                }
                for (auto &value : *m_array)
                {
                    value.print(printer);
                    printer.print(",");
                    if (printer.getIdentation() > 0)
                        printer.println();
                }
                if (printer.getIdentation() > 0)
                    printer.backspaceln();
                printer.backspace();
                if (printer.getIdentation() > 0)
                {
                    printer.dedent();
                    printer.println();
                }
            }
            printer.print("]");
            break;
        case Object:
            printer.print("{");
            if (m_object->size() > 0)
            {
                if (printer.getIdentation() > 0)
                {
                    printer.ident();
                    printer.println();
                }
                for (auto &pair : *m_object)
                {
                    printer.print('"' + pair.first + "\":");
                    if (printer.getIdentation() > 0)
                        printer.print(" ");

                    pair.second.print(printer);
                    printer.print(",");
                    if (printer.getIdentation() > 0)
                        printer.println();
                }
                if (printer.getIdentation() > 0)
                    printer.backspaceln();
                printer.backspace();
                if (printer.getIdentation() > 0)
                {
                    printer.dedent();
                    printer.println();
                }
            }
            printer.print("}");
            break;
        }
    }

    void JsonValue::scan(JsonScanner &scanner)
    {
        drop();
        scanner.dropBlank();
        if (scanner.scanNumber())
        {
            auto token = scanner.take();
            m_kind = Number;
            m_number = std::stod(token);
            return;
        }
        if (scanner.scanString())
        {
            auto token = scanner.take();
            m_kind = String;
            m_string = new std::string(token.substr(1, token.size() - 2));
            return;
        }
        if (scanner.scanBoolean())
        {
            auto token = scanner.take();
            m_kind = Boolean;
            m_boolean = token == "true";
            return;
        }
        if (scanner.scanNull())
        {
            scanner.drop();
            m_kind = Null;
            m_number = 0;
            return;
        }
        if (scanner.dropToken("["))
        {
            m_kind = Array;
            m_array = new std::vector<JsonValue>();
            scanner.dropBlank();
            if (!scanner.dropToken("]"))
            {
            array_item:
                m_array->push_back(nullptr);
                m_array->back().scan(scanner);
                scanner.dropBlank();
                if (scanner.dropToken(","))
                    goto array_item;
                if (!scanner.dropToken("]"))
                    throw std::runtime_error("JSON parse error: unclosed array");
            }
            return;
        }
        if (scanner.dropToken("{"))
        {
            m_kind = Object;
            m_object = new std::unordered_map<std::string, JsonValue>();
            scanner.dropBlank();
            if (!scanner.dropToken("}"))
            {
            property_item:
                scanner.dropBlank();
                if (!scanner.scanString())
                    throw std::runtime_error("JSON parse error: expected property name");
                auto token = scanner.take();
                auto name = token.substr(1, token.size() - 2);
                scanner.dropBlank();
                if (!scanner.dropToken(":"))
                    throw std::runtime_error("JSON parse error: expected ':'");
                m_object->operator[](name) = nullptr;
                m_object->at(name).scan(scanner);
                scanner.dropBlank();
                if (scanner.dropToken(","))
                    goto property_item;
                if (!scanner.dropToken("}"))
                    throw std::runtime_error("JSON parse error: unclosed object");
            }
            return;
        }
        throw std::runtime_error("JSON parse error: unknown value");
    }

    std::string JsonValue::toString(szt identation) const
    {
        std::string string;
        JsonPrinter printer{};
        printer.setTarget(&string);
        printer.setIdentation(identation);
        print(printer);
        return string;
    }

    void JsonValue::fromString(const std::string &string)
    {
        JsonScanner scanner{};
        scanner.setSource(&string);
        scan(scanner);
    }

    void JsonValue::toFile(const std::filesystem::path &path, szt identation) const
    {
        std::ofstream stream{path};
        if (!stream.is_open())
            throw std::runtime_error("Can not open the file");
        std::string string = toString(identation);
        stream << string;
    }

    void JsonValue::fromFile(const std::filesystem::path &path)
    {
        std::ifstream stream{path};
        if (!stream.is_open())
            throw std::runtime_error("Can not open the file");
        std::string string{std::istreambuf_iterator<c8t>(stream), std::istreambuf_iterator<c8t>()};
        fromString(string);
    }

    bool JsonValue::equals(const JsonValue &other) const
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

    JsonValue::JsonValue(f64t number)
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

    const JsonValue &JsonValue::operator[](szt index) const
    {
        return at(index);
    }

    JsonValue &JsonValue::operator[](szt index)
    {
        return at(index);
    }

    const JsonValue &JsonValue::operator[](const std::string &key) const
    {
        return at(key);
    }

    JsonValue &JsonValue::operator[](const std::string &key)
    {
        return at(key);
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
        return equals(other);
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