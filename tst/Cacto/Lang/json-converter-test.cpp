#include <iostream>
#include <sstream>
#include <Cacto/Lang/JsonConverter.hpp>

class JsonClass
{

public:
    int value{};

    virtual ~JsonClass() = default;
};

class JsonClassConverter : public virtual cacto::JsonConverter<JsonClass>
{

public:
    cacto::JsonValue toJson(const JsonClass *const value) const override
    {
        if (value && typeid(*value) == typeid(JsonClass))
            return {std::pair{"$type", "JsonClass"}, std::pair{"value", value->value}};
        return nullptr;
    }

    JsonClass *fromJson(const cacto::JsonValue &json) const override
    {
        if (json.isObject() && json["$type"] == "JsonClass")
        {
            auto instance = new JsonClass();
            instance->value = json["value"].asNumber();
            return instance;
        }
        return nullptr;
    }
};

JsonClassConverter Converter{};

class SubJsonClass
    : public JsonClass
{
public:
    int otherValue{};
};

class SubJsonClassConverter
    : public virtual cacto::JsonConverter<SubJsonClass>,
      public virtual JsonClassConverter
{

public:
    cacto::JsonValue toJson(const JsonClass *const value) const override
    {
        if (value)
        {
            auto json = cacto::toJson(dynamic_cast<const SubJsonClass *>(value));
            return json;
        }
        return nullptr;
    }

    cacto::JsonValue toJson(const SubJsonClass *const value) const override
    {
        if (value && typeid(*value) == typeid(SubJsonClass))
        {
            auto instance = dynamic_cast<const SubJsonClass *>(value);
            return {std::pair{"$type", "SubJsonClass"}, std::pair{"value", instance->value}, std::pair{"otherValue", instance->otherValue}};
        }
        return nullptr;
    }

    SubJsonClass *fromJson(const cacto::JsonValue &json) const override
    {
        if (json.isObject() && json["$type"] == "SubJsonClass")
        {
            auto instance = new SubJsonClass();
            instance->value = int(json["value"].asNumber());
            instance->otherValue = int(json["otherValue"].asNumber());
            return instance;
        }
        return nullptr;
    }
};

SubJsonClassConverter SubConverter{};

class SubSubJsonClass
    : public SubJsonClass
{
public:
    int subOtherValue{};
};

class SubSubJsonClassConverter
    : public virtual cacto::JsonConverter<SubSubJsonClass>,
      public virtual SubJsonClassConverter
{

public:
    cacto::JsonValue toJson(const SubJsonClass *const value) const override
    {
        if (value)
        {
            auto json = cacto::toJson(dynamic_cast<const SubSubJsonClass *>(value));
            return json;
        }
        return nullptr;
    }

    cacto::JsonValue toJson(const SubSubJsonClass *const value) const override
    {
        if (value && typeid(*value) == typeid(SubSubJsonClass))
        {
            auto instance = dynamic_cast<const SubSubJsonClass *>(value);
            return {std::pair{"$type", "SubJsonClass"}, std::pair{"value", instance->value}, std::pair{"otherValue", instance->otherValue}, std::pair{"subOtherValue", instance->subOtherValue}};
        }
        return nullptr;
    }

    SubSubJsonClass *fromJson(const cacto::JsonValue &json) const override
    {
        if (json.isObject() && json["$type"] == "SubSubJsonClass")
        {
            auto instance = new SubSubJsonClass();
            instance->value = int(json["value"].asNumber());
            instance->otherValue = int(json["otherValue"].asNumber());
            instance->subOtherValue = int(json["subOtherValue"].asNumber());
            return instance;
        }
        return nullptr;
    }
};

SubSubJsonClassConverter SubSubConverter{};

int main()
{

    std::stringstream text{R"({"$type":"SubSubJsonClass","value":25,"otherValue":75,"subOtherValue":475})"};
    cacto::JsonValue json{};
    text >> json;
    auto instance = cacto::fromJson<JsonClass>(json);
    instance->value = 32;
    json = cacto::toJson(instance);
    std::cout << json;

    return 0;
}