#include <iostream>

#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Json.hpp>
#include <Cacto/Lang/Utils.hpp>

class ModelExample
    : public virtual cacto::Json
{

public:
    cacto::JsonValue toJson() const override
    {
        auto json = cacto::JsonValue::ObjectValue;
        json["value"] = double(value);
        return json;
    }

    void fromJson(const cacto::JsonValue &json) override
    {
        value = int(json["value"].asNumber());
    }

    int value{};
};

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
    std::cout << json.toString(2) << '\n';

    auto doc = json.toString(2);
    auto text = "25";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    text = "\"String\"";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    text = "true";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    text = "null";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    text = "[0, 1, 2, 3, 4, 5]";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    text = "{\"name\": \"value\"}";
    json.fromString(text);
    std::cout << json.toString(2) << '\n';

    json.fromString(doc);
    std::cout << json.toString(2) << '\n';

    ModelExample model;
    model.value = 23;
    json = model.toJson();
    std::cout << json.toString(2) << '\n';
    model.value = 0;
    model.fromJson(json);

    json = "String with \" escapes";
    std::cout << json.asString() << '\n';
    std::cout << json.toString() << '\n';
    string = json.toString();
    json.fromString(string);
    std::cout << json.toString() << '\n';

    return 0;
}