#include <iostream>

#include <Cacto/Lang/JsonScanner.hpp>

int main()
{

    cacto::JsonScanner scanner;
    std::string string;
    while (true)
    {
        std::cin >> string;
        if (string == "exit")
            break;
        scanner.setSource(&string);
        auto index = scanner.scanString();
        auto token = scanner.take();
        std::cout << "Token: " << token << '\n';
    }

    return 0;
}