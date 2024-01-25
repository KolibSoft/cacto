#include <sstream>
#include <iostream>
#include <fstream>
#include <Cacto/Lang/Printable.hpp>
#include <Cacto/Lang/Printer.hpp>

class PrintableClass : public cacto::Printable
{

public:
    int value{0};

    void print(cacto::Printer &printer) const override
    {
        printer.println("My Value Is:");
        printer.ident(4);
        printer.println(std::to_string(value));
        printer.dedent(4);
    }
};

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
    printer.println();

    std::ifstream fstream{"res/file.txt"};
    printer.println(fstream);

    PrintableClass printable{};
    std::cout << printable;

    return 0;
}