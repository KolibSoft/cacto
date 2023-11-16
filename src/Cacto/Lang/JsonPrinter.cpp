#include <Cacto/Lang/JsonPrinter.hpp>

namespace cacto
{

    void JsonPrinter::printNumber(f64t value)
    {
        print(std::to_string(value));
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