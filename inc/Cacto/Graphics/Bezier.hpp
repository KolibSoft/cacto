#pragma once

#include <vector>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class JsonValue;

    class CACTO_GRAPHICS_API Bezier final
        : public virtual Line
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        const std::vector<sf::Vector2f> &asPoints() const;
        std::vector<sf::Vector2f> &asPoints();

        Bezier(const std::vector<sf::Vector2f> &points = {});
        virtual ~Bezier();

    private:
        std::vector<sf::Vector2f> m_points;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Bezier &bezier);
    void CACTO_GRAPHICS_API fromXml(Bezier &bezier, const XmlValue &xml);

    namespace bezier
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
