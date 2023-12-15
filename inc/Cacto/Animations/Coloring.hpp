#pragma once

#include <SFML/Graphics/Color.hpp>
#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Coloring
        : public Animation
    {

    public:
        const sf::Color &getFrom() const;
        void setFrom(const sf::Color &value);

        const sf::Color &getTo() const;
        void setTo(const sf::Color &value);

        sf::Color getValue(const sf::Time &lifetime) const;

        Coloring(const sf::Color &from = sf::Color::White, const sf::Color &to = sf::Color::White, const sf::Time &delay = sf::Time::Zero, const sf::Time &duration = sf::Time::Zero, Direction direction = Forward, Mode mode = Once);
        virtual ~Coloring();

    private:
        sf::Color m_from;
        sf::Color m_to;
    };

    JsonValue CACTO_ANIMATIONS_API toJson(const Coloring &coloring);
    void CACTO_ANIMATIONS_API fromJson(Coloring &coloring, const JsonValue &json);

    namespace coloring
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
