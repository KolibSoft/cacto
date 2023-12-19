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

    JsonValue CACTO_GRAPHICS_API toJson(const Straight &straight);
    void CACTO_GRAPHICS_API fromJson(Straight &straight, const JsonValue &json);

    namespace straight
    {

        class CACTO_GRAPHICS_API JsonConverter
            : public virtual line::JsonConverter
        {

        public:
            JsonValue toJson(const Shared<const Line> &value) const override;
            Shared<Line> fromJson(const JsonValue &json) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

        extern JsonConverter CACTO_GRAPHICS_API Converter;

    }

}
