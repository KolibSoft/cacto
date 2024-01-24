#include <iostream>
#include <fstream>
#include <Cacto/Lang/Printer.hpp>

int main()
{

    cacto::Printer printer{std::cout};
    printer.println("=== HEADER ===");
    printer.ident(4);
    printer.println("Idented line");
    printer.ident(4);
    printer.print("KEY");
    printer.print(": ");
    printer.print("VALUE");
    printer.dedent(4);
    printer.flush();

    return 0;
}