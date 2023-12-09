#include <string>

int main() {
    std::string string = u8"Esto funciona";
    int value = std::stoi("FF", 0, 16);

    return 0;
}