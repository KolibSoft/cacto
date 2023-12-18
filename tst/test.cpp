#include <string>
#include <iostream>
#include <filesystem>

#include <Dylib/dylib.hpp>
#include <Cacto/Core/Object.hpp>

int main()
{

    dylib lib("./lib.dll");

    auto dynamicTest = lib.get_function<std::string *(const std::string *)>("dynamicTest");
    std::string message = "Message";
    auto result = dynamicTest(&message);
    std::cout << *result << '\n';

    // cacto::Object object{};
    auto ptr = std::make_shared<cacto::Object>();
    auto _ptr = ptr->as();
    auto cast = ptr->as<std::string>();

    return 0;
}