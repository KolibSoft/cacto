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
    auto number = json.asNumber();

    json = "String";
    kind = json.getKind();
    comparison = json == "String";
    auto string = json.asString();

    json = true;
    kind = json.getKind();
    comparison = json == true;
    auto boolean = json.asBoolean();

    json = nullptr;
    kind = json.getKind();
    comparison = json == nullptr;

    json = {25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    auto array = json.asArray();

    json = {std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    auto object = json.asObject();

    json = cacto::JsonValue::ArrayValue;
    json.asArray().push_back(25);
    json.asArray().push_back("String");
    json.asArray().push_back(true);
    json.asArray().push_back(nullptr);
    json.asArray().push_back({25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()});
    json.asArray().push_back({std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}});
    json[5]["object"] = json;

    return 0;
}