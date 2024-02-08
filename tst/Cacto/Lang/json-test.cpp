#include <iostream>

#include <Cacto/Lang/JsonValue.hpp>

int main()
{

    cacto::JsonValue json{};
    auto kind = json.getType();
    auto comparison = json == nullptr;

    json = 25;
    kind = json.getType();
    comparison = json == 25;
    auto number = (double)json;

    json = "String";
    kind = json.getType();
    comparison = json == "String";
    auto string = (std::string)json;

    json = true;
    kind = json.getType();
    comparison = json == true;
    auto boolean = (bool)json;

    json = nullptr;
    kind = json.getType();
    comparison = json == nullptr;

    json = {25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    kind = json.getType();
    comparison = json == cacto::JsonValue{25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    auto array = json.asArray();

    json = {std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    kind = json.getType();
    comparison = json == cacto::JsonValue{std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    auto object = json.asObject();

    json.setArray();
    json.append(25);
    json.append("String");
    json.append(true);
    json.append(nullptr);
    json.append({25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()});
    json.append({std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}});
    json[5]["object"] = json;

    json = nullptr;
    const auto &cjson = json;
    std::cout << cjson[0][0][0][0]["Property"]["SubProperty"].getNumber(23) << "\n";

    cacto::JsonValue jsonA = {std::pair{"A", "Value"}};
    cacto::JsonValue jsonB = {std::pair{"A", "Ignored"}};
    std::cout << (jsonA | jsonB) << "\n";

    return 0;
}