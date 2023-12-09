#include <sstream>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Lang/JsonPrinter.hpp>

namespace cacto
{

    void JsonPrinter::printNumber(f64t value)
    {
        std::stringstream stream{};
        stream << value;
        print(stream.str());
    }

    void JsonPrinter::printString(const std::string &value)
    {
        auto string = value;
        replace(string, "\\", "\\\\");
        replace(string, "\"", "\\\"");
        replace(string, "/", "\\/");
        replace(string, "\b", "\\b");
        replace(string, "\f", "\\f");
        replace(string, "\n", "\\n");
        replace(string, "\r", "\\r");
        replace(string, "\t", "\\t");
        print('"' + string + '"');
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