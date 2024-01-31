#include <string>
#include <iostream>
#include <filesystem>

#include <Dylib/dylib.hpp>

class Ax{};

int main()
{

    auto *source = new Ax{};
    auto *destination = std::move(source);

    dylib lib("./lib.dll");

    auto dynamicTest = lib.get_function<std::string *(const std::string *)>("dynamicTest");
    std::string message = "Message";
    auto result = dynamicTest(&message);
    std::cout << *result << '\n';

    std::vector<int> vec1{};
    std::vector<int> vec2{};

    return 0;
}