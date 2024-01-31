#include <iostream>

#include <Cacto/Lang/JsonValue.hpp>

int main()
{

    cacto::JsonValue json{};
    auto kind = json.getKind();
    auto comparison = json == nullptr;

    json = 25;
    kind = json.getKind();
    comparison = json == 25;
    auto number = (double)json;

    json = "String";
    kind = json.getKind();
    comparison = json == "String";
    auto string = (std::string)json;

    json = true;
    kind = json.getKind();
    comparison = json == true;
    auto boolean = (bool)json;

    json = nullptr;
    kind = json.getKind();
    comparison = json == nullptr;

    json = {25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    auto array = json.asArray();

    json = {std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    auto object = json.asObject();

    json = cacto::JsonValue::ArrayValue;
    json.append(25);
    json.append("String");
    json.append(true);
    json.append(nullptr);
    json.append({25, "String", true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()});
    json.append({std::pair{"number", 25}, std::pair{"string", "String"}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}});
    json[5]["object"] = json;

    std::cout << json;

    return 0;
}