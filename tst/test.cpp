#include <string>
#include <iostream>
#include <filesystem>

#include <Dylib/dylib.hpp>

int main()
{

    dylib lib("./lib.dll");

    auto dynamicTest = lib.get_function<std::string *(const std::string *)>("dynamicTest");
    std::string message = "Message";
    auto result = dynamicTest(&message);
    std::cout << *result << '\n';

    return 0;
}