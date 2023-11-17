#ifndef CACTO_STRAIGHT_HPP
#define CACTO_STRAIGHT_HPP

#include <Cacto/Lang/Json.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Straight final
        : public virtual Line,
          public virtual Json
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        JsonValue toJson() const override;
        void fromJson(const JsonValue &json) override;

        Straight(const sf::Vector2f &begin = {0, 0}, const sf::Vector2f &end = {0, 0});
        virtual ~Straight();

    private:
        sf::Vector2f m_begin;
        sf::Vector2f m_end;
    };

}

#endif