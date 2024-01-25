#include <iostream>
#include <fstream>
#include <Cacto/Lang/JsonValue.hpp>

int main()
{

    cacto::JsonValue json = nullptr;
    std::ifstream stream{"res/json.json"};
    stream >> json;

    std::cout << json;

    return 0;
}