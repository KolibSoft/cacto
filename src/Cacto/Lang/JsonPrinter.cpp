#include <sstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/StringUtils.hpp>
#include <Cacto/Lang/JsonPrinter.hpp>

namespace cacto
{

    Printer &JsonPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void JsonPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void JsonPrinter::printNumber(f64t number)
    {
        std::stringstream stream{};
        stream << number;
        m_printer->print(stream.str());
    }

    void JsonPrinter::printString(const std::string &string)
    {
        auto escaped = string;
        replace(escaped, "\\", "\\\\");
        replace(escaped, "\"", "\\\"");
        replace(escaped, "/", "\\/");
        replace(escaped, "\b", "\\b");
        replace(escaped, "\f", "\\f");
        replace(escaped, "\n", "\\n");
        replace(escaped, "\r", "\\r");
        replace(escaped, "\t", "\\t");
        m_printer->print('"' + escaped + '"');
    }

    void JsonPrinter::printBoolean(bool boolean)
    {
        m_printer->print(boolean ? "true" : "false");
    }

    void JsonPrinter::printNull()
    {
        m_printer->print("null");
    }

    void JsonPrinter::printArray(const std::vector<JsonValue> &array)
    {
        auto ident = m_printer->getIdentation() > 0;
        m_printer->print("[");
        if (array.size() > 0)
        {
            if (ident)
            {
                m_printer->println();
                m_printer->ident();
            }
            auto it = array.begin();
            std::advance(it, array.size() - 1);
            auto &last = *it;
            for (auto &value : array)
            {
                printJson(value);
                if (&value != &last)
                {
                    m_printer->print(",");
                    if (ident)
                        m_printer->println();
                }
            }
            if (ident)
            {
                m_printer->println();
                m_printer->dedent();
            }
        }
        m_printer->print("]");
    }

    void JsonPrinter::printObject(const std::unordered_map<std::string, JsonValue> &object)
    {
        auto ident = m_printer->getIdentation() > 0;
        m_printer->print("{");
        if (object.size() > 0)
        {
            if (ident)
            {
                m_printer->println();
                m_printer->ident();
            }
            auto it = object.begin();
            std::advance(it, object.size() - 1);
            auto &last = *it;
            for (auto &value : object)
            {
                printString(value.first);
                m_printer->print(":");
                printJson(value.second);
                if (&value != &last)
                {
                    m_printer->print(",");
                    if (ident)
                        m_printer->println();
                }
            }
            if (ident)
            {
                m_printer->println();
                m_printer->dedent();
            }
        }
        m_printer->print("}");
    }

    void JsonPrinter::printJson(const JsonValue &json)
    {
        switch (json.getType())
        {
        case JsonType::Number:
            printNumber(json.getNumber());
            break;
        case JsonType::String:
            printString(json.asString());
            break;
        case JsonType::Boolean:
            printBoolean(json.getBoolean());
            break;
        case JsonType::Null:
            printNull();
            break;
        case JsonType::Array:
            printArray(json.asArray());
            break;
        case JsonType::Object:
            printObject(json.asObject());
            break;
        }
    }

    JsonPrinter::JsonPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    JsonPrinter::~JsonPrinter() = default;

}