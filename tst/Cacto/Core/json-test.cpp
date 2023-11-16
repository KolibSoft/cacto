#include <iostream>

#include <Cacto/Core/JsonValue.hpp>

int main()
{

    cacto::JsonValue json{};
    auto kind = json.getKind();
    auto comparison = json == nullptr;

    json = 25.0;
    kind = json.getKind();
    comparison = json == 25.0;
    auto number = json.asNumber();

    json = std::string("String");
    kind = json.getKind();
    comparison = json == std::string("String");
    auto string = json.asString();

    json = true;
    kind = json.getKind();
    comparison = json == true;
    auto boolean = json.asBoolean();

    json = nullptr;
    kind = json.getKind();
    comparison = json == nullptr;

    json = std::vector<cacto::JsonValue>{25.0, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    kind = json.getKind();
    comparison = json == std::vector<cacto::JsonValue>{25.0, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    auto array = json.asArray();

    json = std::unordered_map<std::string, cacto::JsonValue>{{"number", 25.0}, {"string", std::string("String")}, {"boolean", true}, {"null", nullptr}, {"array", std::vector<cacto::JsonValue>()}, {"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    kind = json.getKind();
    comparison = json == std::unordered_map<std::string, cacto::JsonValue>{{"number", 25.0}, {"string", std::string("String")}, {"boolean", true}, {"null", nullptr}, {"array", std::vector<cacto::JsonValue>()}, {"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    auto object = json.asObject();

    return 0;
}