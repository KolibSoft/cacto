#include <iostream>
#include <fstream>
#include <Cacto/Lang/JsonValue.hpp>

int main()
{

    cacto::JsonValue json = nullptr;
    std::ofstream stream{"res/json.json"};

    json = {std::pair{"A", 0}, std::pair{"B", 1}};
    stream << json;

    return 0;
}