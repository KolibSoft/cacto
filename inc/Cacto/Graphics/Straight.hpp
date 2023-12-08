#ifndef CACTO_STRAIGHT_HPP
#define CACTO_STRAIGHT_HPP

#include <SFML/System/Vector2.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
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
            : public virtual cacto::JsonConverter<Line>
        {

        public:
            JsonValue toJson(const Line *const value) const override;
            Line *fromJson(const JsonValue &json) const override;

            JsonConverter();
            virtual ~JsonConverter();
        } Converter{};
    }

}

#endif