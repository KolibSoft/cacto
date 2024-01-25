#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Printer;
    class JsonValue;

    class CACTO_LANG_API JsonPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printNumber(f64t number);
        void printString(const std::string &string);
        void printBoolean(bool boolean);
        void printNull();

        void printArray(const std::vector<JsonValue> &array);
        void printObject(const std::unordered_map<std::string, JsonValue> &object);
        void printJson(const JsonValue &json);

        JsonPrinter(Printer &printer);
        virtual ~JsonPrinter();

    private:
        Printer *m_printer;
    };

}
