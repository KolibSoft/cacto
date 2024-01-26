#include <iostream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/JsonPack.hpp>

int main()
{

    cacto::JsonPack pack{"res/jsons"};
    auto json = cacto::getResource<cacto::JsonValue>("my_json.json");
    std::cout << "Json content: " << (json ? *json : cacto::JsonValue::NullValue) << '\n';

    return 0;
}