#pragma once

#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Linear
        : public Animation
    {

    public:
        const f32t &getFrom() const;
        void setFrom(const f32t &value);

        const f32t &getTo() const;
        void setTo(const f32t &value);

        f32t getValue(const sf::Time &lifetime) const;

        Linear(f32t from = 0, f32t to = 0, const sf::Time &delay = sf::Time::Zero, const sf::Time &duration = sf::Time::Zero, Direction direction = Forward, Mode mode = Once);
        virtual ~Linear();

    private:
        f32t m_from;
        f32t m_to;
    };

    JsonValue CACTO_ANIMATIONS_API toJson(const Linear &linear);
    void CACTO_ANIMATIONS_API fromJson(Linear &linear, const JsonValue &json);

    namespace linear
    {

        class CACTO_ANIMATIONS_API JsonConverter
            : public virtual animation::JsonConverter
        {

        public:
            JsonValue toJson(const Animation *const value) const override;
            Animation *fromJson(const JsonValue &json) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

        extern JsonConverter CACTO_ANIMATIONS_API Converter;

    }

}
