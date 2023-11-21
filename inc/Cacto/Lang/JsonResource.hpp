#ifndef CACTO_JSON_RESOURCE_HPP
#define CACTO_JSON_RESOURCE_HPP

#include <functional>
#include <Cacto/Lang/Json.hpp>

namespace cacto
{

    class CACTO_LANG_API JsonResource
        : public virtual Json
    {

    public:
        const Json *const getJson() const;
        Json *const getJson();

        JsonValue toJson() const override;
        void fromJson(const JsonValue &json) override;

        JsonResource(const std::string &type = "", Json *const json = nullptr);
        virtual ~JsonResource();

        JsonResource(const JsonResource &other) = delete;
        JsonResource &operator=(const JsonResource &other) = delete;

        JsonResource(JsonResource &&other);
        JsonResource &operator=(JsonResource &&other);

        static std::unordered_map<std::string, std::function<Json *()>> Registry;

    private:
        void drop();

        std::string m_type;
        Json *m_json;
    };

}

#endif