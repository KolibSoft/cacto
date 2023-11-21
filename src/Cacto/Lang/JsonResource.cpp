#include <Cacto/Lang/JsonResource.hpp>

namespace cacto
{

    const Json *const JsonResource::getJson() const
    {
        return m_json;
    }

    Json *const JsonResource::getJson()
    {
        return m_json;
    }

    JsonValue JsonResource::toJson() const
    {
        if (m_json)
        {
            auto json = JsonValue::ObjectValue;
            json["type"] = m_type;
            auto data = m_json->toJson();
            json["data"] = data;
            return json;
        }
        return nullptr;
    }

    void JsonResource::fromJson(const JsonValue &json)
    {
        drop();
        if (json != nullptr)
        {
            m_type = json["type"].asString();
            auto &registry = Registry[m_type];
            if (registry == nullptr)
                throw std::runtime_error("Not registered JSON type");
            auto data = json["data"];
            auto _json = registry();
            _json->fromJson(data);
            m_json = _json;
        }
    }

    JsonResource::JsonResource(const std::string &type, Json *const json)
        : m_type(type),
          m_json(json)
    {
    }

    JsonResource::~JsonResource()
    {
        drop();
    }

    JsonResource::JsonResource(JsonResource &&other)
        : m_type(),
          m_json(nullptr)
    {
        *this = std::move(other);
    }

    JsonResource &JsonResource::operator=(JsonResource &&other)
    {
        drop();
        m_type = other.m_type;
        m_json = other.m_json;
        other.m_type.clear();
        other.m_json = nullptr;
        return *this;
    }

    std::unordered_map<std::string, std::function<Json *()>> JsonResource::Registry{};

    void JsonResource::drop()
    {
        m_type.clear();
        if (m_json)
        {
            delete m_json;
            m_json = nullptr;
        }
    }

}