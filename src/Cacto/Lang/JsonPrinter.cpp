#include <Cacto/Lang/JsonPrinter.hpp>

namespace cacto
{

    void JsonPrinter::printNumber(f64t value)
    {
        auto string = std::to_string(value);
        if (string.find('.') != std::string::npos && string.find('E') == std::string::npos && string.find('e') == std::string::npos)
        {
            while (string.back() == '0')
                string.pop_back();
            string.pop_back();
        }
        print(string);
    }

    void JsonPrinter::printString(const std::string &value)
    {
        print('"' + value + '"');
    }

    void JsonPrinter::printBoolean(bool value)
    {
        print(value ? "true" : "false");
    }

    void JsonPrinter::printNull()
    {
        print("null");
    }

    JsonPrinter::JsonPrinter() = default;
    JsonPrinter::~JsonPrinter() = default;

}