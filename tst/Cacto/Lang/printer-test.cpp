#include <iostream>
#include <fstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>

int main()
{

    std::ofstream ofstream{"res/file.txt"};
    cacto::Printer printer{ofstream};
    printer.setIdentation(2);
    printer.ident(1);
    printer.print("Buffered ");
    printer.print("line ");
    printer.print("data");
    printer.println();
    printer.print("Another buffered line error");
    printer.backspace(5);
    printer.println();
    printer.print("error error error error");
    printer.backspaceln();
    printer.flush();
    ofstream.close();

    std::ifstream ifstream{"res/file.txt"};
    cacto::Scanner scanner{ifstream};
    while (scanner.available() || scanner.scanln())
    {
        scanner.dropBlank();
        scanner.scanWord();
        auto token = scanner.take();
        std::cout << token << '\n';
    }
    ifstream.close();

    return 0;
}