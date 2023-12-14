#include <iostream>
#include <fstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>

int main()
{

    std::fstream fstream{"res/file.txt"};
    cacto::Printer printer{fstream};
    printer
        .print("Buffered ")
        .print("line ")
        .print("data")
        .println()
        .print("Another buffered line error")
        .backspace(5)
        .println()
        .print("error error error error")
        .backspaceln()
        .flush();

    return 0;
}