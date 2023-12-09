#include <string>
#include <iostream>

int main() {
    std::string string = u8"Esto funciona";
    int value = std::stoi("FF", 0, 16);

    std::cout << 1234.56 << "\n";

    return 0;
}