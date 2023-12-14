#include <iostream>

#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    cacto::JsonValue json{};
    auto kind = json.getKind();
    auto comparison = json == nullptr;
    std::cout << json << '\n';

    json = 25;
    kind = json.getKind();
    comparison = json == 25;
    auto number = json.asNumber();
    std::cout << json << '\n';

    json = "String";
    kind = json.getKind();
    comparison = json == "String";
    auto string = json.asString();
    std::cout << json << '\n';

    json = true;
    kind = json.getKind();
    comparison = json == true;
    auto boolean = json.asBoolean();
    std::cout << json << '\n';

    json = nullptr;
    kind = json.getKind();
    comparison = json == nullptr;
    std::cout << json << '\n';

    json = {25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()};
    auto array = json.asArray();
    std::cout << json << '\n';

    json = {std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    kind = json.getKind();
    comparison = json == cacto::JsonValue{std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}};
    auto object = json.asObject();
    std::cout << json << '\n';

    json = cacto::JsonValue::ArrayValue;
    json.asArray().push_back(25);
    json.asArray().push_back("String");
    json.asArray().push_back(true);
    json.asArray().push_back(nullptr);
    json.asArray().push_back({25, std::string("String"), true, nullptr, std::vector<cacto::JsonValue>(), std::unordered_map<std::string, cacto::JsonValue>()});
    json.asArray().push_back({std::pair{"number", 25}, std::pair{"string", std::string("String")}, std::pair{"boolean", true}, std::pair{"null", nullptr}, std::pair{"array", std::vector<cacto::JsonValue>()}, std::pair{"object", std::unordered_map<std::string, cacto::JsonValue>()}});
    json[5]["object"] = json;
    json.toStream(std::cout, 2);

    auto doc = json.toString(2);
    auto text = "25";
    json.fromString(text);
    json.toStream(std::cout, 2);

    text = "\"String\"";
    json.fromString(text);
    json.toStream(std::cout, 2);

    text = "true";
    json.fromString(text);
    json.toStream(std::cout, 2);

    text = "null";
    json.fromString(text);
    json.toStream(std::cout, 2);

    text = "[0, 1, 2, 3, 4, 5]";
    json.fromString(text);
    json.toStream(std::cout, 2);

    text = "{\"name\": \"value\"}";
    json.fromString(text);
    json.toStream(std::cout, 2);

    json.fromString(doc);
    json.toStream(std::cout, 2);

    json = "String with \" escapes";
    std::cout << json.asString() << '\n';
    std::cout << json << '\n';
    string = json.toString();
    json.fromString(string);
    std::cout << json << '\n';

    return 0;
}