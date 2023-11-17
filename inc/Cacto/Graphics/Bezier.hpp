#ifndef CACTO_BEZIER_HPP
#define CACTO_BEZIER_HPP

#include <vector>
#include <Cacto/Lang/Json.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Bezier final
        : public virtual Line,
          public virtual Json
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        JsonValue toJson() const override;
        void fromJson(const JsonValue &json) override;

        Bezier(const std::vector<sf::Vector2f> &points = {});
        virtual ~Bezier();

    private:
        std::vector<sf::Vector2f> m_points;
    };

}

#endif