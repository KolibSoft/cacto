#ifndef CACTO_BEZIER_HPP
#define CACTO_BEZIER_HPP

#include <vector>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Bezier final
        : public virtual Line
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        const sf::Vector2f &getControlPoint(szt index) const;
        void setControlPoint(szt index, const sf::Vector2f &value);

        void clear();
        void append(const sf::Vector2f &point);
        void resize(szt count);

        Bezier(const std::vector<sf::Vector2f> &points = {});
        virtual ~Bezier();

    private:
        std::vector<sf::Vector2f> m_points;
    };

    namespace bezier
    {

        class CACTO_GRAPHICS_API JsonConverter
            : public virtual line::JsonConverter
        {
        public:
            JsonValue toJson(const Line *const value) const override;
            Line *fromJson(const JsonValue &json) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

        extern JsonConverter CACTO_GRAPHICS_API Converter;

    }

}

#endif