#include <sstream>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/StringUtils.hpp>
#include <Cacto/Lang/JsonScanner.hpp>

namespace cacto
{

    Scanner &JsonScanner::getScanner() const
    {
        return *m_scanner;
    }

    void JsonScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool JsonScanner::scanNumber(f64t &number)
    {
        auto scanExponent = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanClass("Ee", false, 1, 1) && m_scanner->scanClass("+-", true, 1, 1) && m_scanner->scanDigit())
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto scanFraction = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken(".") && m_scanner->scanDigit())
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()) && m_scanner->option(scanExponent()))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> number;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanString(std::string &string)
    {
        auto scanEscape = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken("\\") && m_scanner->scanClass("\"\\/bfnrt", false, 1, 1))
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanToken("\""))
        {
            while (scanEscape() || m_scanner->scanNotClass("\"\\"))
                continue;
            if (m_scanner->scanToken("\""))
            {
                auto token = m_scanner->take();
                string = std::string(token.substr(1, token.size() - 2));
                replace(string, "\\\"", "\"");
                replace(string, "\\/", "/");
                replace(string, "\\b", "\b");
                replace(string, "\\f", "\f");
                replace(string, "\\n", "\n");
                replace(string, "\\r", "\r");
                replace(string, "\\t", "\t");
                replace(string, "\\\\", "\\");
                return true;
            }
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanBoolean(bool &boolean)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanToken("true") || m_scanner->scanToken("false"))
        {
            auto token = m_scanner->take();
            boolean = token == "true";
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanNull()
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanToken("null"))
            return true;
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanArray(std::vector<JsonValue> &array)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->dropToken("["))
        {
            array.clear();
            m_scanner->dropBlankln();
            if (!m_scanner->dropToken("]"))
            {
            array_item:
                m_scanner->dropBlankln();
                array.push_back(nullptr);
                scanJson(array.back());
                m_scanner->dropBlankln();
                if (m_scanner->dropToken(","))
                    goto array_item;
                if (!m_scanner->dropToken("]"))
                    throw std::runtime_error("Unclosed json array");
            }
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanObject(std::unordered_map<std::string, JsonValue> &object)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->dropToken("{"))
        {
            object.clear();
            m_scanner->dropBlankln();
            if (!m_scanner->dropToken("}"))
            {
            property_item:
                std::string name{};
                m_scanner->dropBlankln();
                if (!scanString(name))
                    throw std::runtime_error("Expected property name");
                m_scanner->dropBlankln();
                if (!m_scanner->dropToken(":"))
                    throw std::runtime_error("Expected ':'");
                m_scanner->dropBlankln();
                object[name] = nullptr;
                scanJson(object[name]);
                m_scanner->dropBlankln();
                if (m_scanner->dropToken(","))
                    goto property_item;
                if (!m_scanner->dropToken("}"))
                    throw std::runtime_error("Unclosed json object");
            }
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanJson(JsonValue &json)
    {
        f64t number = 0;
        if (scanNumber(number))
        {
            json = number;
            return true;
        }

        std::string string{};
        if (scanString(string))
        {
            json = string;
            return true;
        }

        bool boolean = false;
        if (scanBoolean(boolean))
        {
            json = boolean;
            return true;
        }

        if (scanNull())
        {
            json = nullptr;
            return true;
        }

        std::vector<JsonValue> array{};
        if (scanArray(array))
        {
            json = array;
            return true;
        }

        std::unordered_map<std::string, JsonValue> object{};
        if (scanObject(object))
        {
            json = object;
            return true;
        }

        return false;
    }

    JsonScanner::JsonScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    JsonScanner::~JsonScanner() = default;

}