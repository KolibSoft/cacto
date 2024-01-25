#include <iostream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Printer.hpp>

int main()
{

    cacto::JsonValue json = nullptr;
    cacto::Printer printer{std::cout};

    json = {std::pair{"A", 0}, std::pair{"B", 1}};
    printer.setIdentation(0);
    printer.print(json);
    printer.flush();

    return 0;
}