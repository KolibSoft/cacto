#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Scanner;
    class JsonValue;

    class CACTO_LANG_API JsonScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanNumber(f64t &number);
        bool scanString(std::string &string);
        bool scanBoolean(bool &boolean);
        bool scanNull();

        bool scanArray(std::vector<JsonValue> &array);
        bool scanObject(std::unordered_map<std::string, JsonValue> &object);
        bool scanJson(JsonValue &json);

        JsonScanner(Scanner &scanner);
        virtual ~JsonScanner();

    private:
        Scanner *m_scanner;
    };

}
