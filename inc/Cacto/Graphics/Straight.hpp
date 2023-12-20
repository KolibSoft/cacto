#pragma once

#include <SFML/System/Vector2.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Straight final
        : public virtual Line
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        const sf::Vector2f &getBegin() const;
        void setBegin(const sf::Vector2f &value);

        const sf::Vector2f &getEnd() const;
        void setEnd(const sf::Vector2f &value);

        Straight(const sf::Vector2f &begin = {0, 0}, const sf::Vector2f &end = {0, 0});
        virtual ~Straight();

    private:
        sf::Vector2f m_begin;
        sf::Vector2f m_end;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Straight &straight);
    void CACTO_GRAPHICS_API fromXml(Straight &straight, const XmlValue &xml);

    namespace straight
    {

        class CACTO_GRAPHICS_API XmlConverter
            : public line::XmlConverter
        {

        public:
            XmlValue toXml(const Shared<const Line> &value) const override;
            Shared<Line> fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_GRAPHICS_API Converter;

    }

}
