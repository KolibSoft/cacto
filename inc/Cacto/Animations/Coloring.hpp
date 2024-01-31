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

    XmlValue CACTO_ANIMATIONS_API toXml(const Coloring &coloring);
    Coloring CACTO_ANIMATIONS_API toColoring(const XmlValue &xml);

    namespace coloring
    {

        class CACTO_ANIMATIONS_API XmlConverter
            : public virtual animation::XmlConverter
        {
        public:
            XmlValue toXml(const Animation *const value) const override;
            Animation *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_ANIMATIONS_API Converter;

    }

}
