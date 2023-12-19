#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/Ellipse.hpp>

namespace cacto
{

    std::size_t Ellipse::getPointCount() const
    {
        return 12;
    }

    sf::Vector2f Ellipse::getPoint(std::size_t index, std::size_t precision) const
    {
        if (precision < 1)
            precision = 1;
        auto count = 12 * precision;
        auto point = sf::Vector2f(
            m_centerX + m_radiusX * cosf((index * 2 * M_PI) / count),
            m_centerY + m_radiusY * sinf((index * 2 * M_PI) / count));
        return point;
    }

    sf::FloatRect Ellipse::getBounds() const
    {
        auto bounds = sf::FloatRect({m_left, m_top}, {m_right - m_left, m_bottom - m_top});
        return bounds;
    }

    bool Ellipse::containsPoint(const sf::Vector2f &point) const
    {
        if (
            point.x >= m_left && point.x <= m_right &&
            point.y >= m_top && point.y <= m_bottom)
        {
            auto dx = point.x - m_centerX;
            auto dy = point.y - m_centerY;
            auto result = ((dx * dx) / (m_radiusX * m_radiusX) +
                               (dy * dy) / (m_radiusY * m_radiusY) <=
                           1);
            return result;
        }
        return false;
    }

    const sf::Vector2f Ellipse::getCenter() const
    {
        return {m_centerX, m_centerY};
    }

    void Ellipse::setCenter(const sf::Vector2f &value)
    {
        m_centerX = value.x;
        m_centerY = value.y;
        m_left = m_centerX - m_radiusX;
        m_right = m_centerX + m_radiusX;
        m_top = m_centerY - m_radiusY;
        m_bottom = m_centerY + m_radiusY;
    }

    const sf::Vector2f Ellipse::getDiameters() const
    {
        return {m_radiusX * 2, m_radiusY * 2};
    }

    void Ellipse::setDiameters(const sf::Vector2f &value)
    {
        m_radiusX = value.x / 2;
        m_radiusY = value.y / 2;
        m_left = m_centerX - m_radiusX;
        m_right = m_centerX + m_radiusX;
        m_top = m_centerY - m_radiusY;
        m_bottom = m_centerY + m_radiusY;
    }

    Ellipse::Ellipse(const sf::Vector2f &center, const sf::Vector2f &diameters)
        : m_centerX(center.x), m_centerY(center.y),
          m_radiusX(diameters.x / 2), m_radiusY(diameters.y / 2),
          m_left(center.x - diameters.x / 2), m_top(center.y - diameters.y / 2),
          m_right(center.x + diameters.x / 2), m_bottom(center.y + diameters.y / 2)
    {
    }

    Ellipse::~Ellipse() = default;

    const Ellipse Ellipse::Identity{{0, 0}, {1, 1}};

    JsonValue CACTO_GRAPHICS_API toJson(const Ellipse &ellipse)
    {
        auto json = JsonValue::ObjectValue;
        auto center = ellipse.getCenter();
        auto diameters = ellipse.getDiameters();
        json["center"] = {center.x, center.y};
        json["diameters"] = {diameters.x, diameters.y};
        return json;
    }

    void CACTO_GRAPHICS_API fromJson(Ellipse &ellipse, const JsonValue &json)
    {
        auto &center = json["center"];
        auto &diameters = json["diameters"];
        ellipse.setCenter({f32t(center[0].getNumber()), f32t(center[1].getNumber())});
        ellipse.setDiameters({f32t(diameters[0].getNumber()), f32t(diameters[1].getNumber())});
    }

    namespace ellipse
    {

        JsonValue JsonConverter::toJson(const Shared<const Geometry> &value) const
        {
            Shared<const Ellipse> ellipse = nullptr;
            auto ptr = value.get();
            if (value && typeid(*ptr) == typeid(Ellipse) && (ellipse = std::dynamic_pointer_cast<const Ellipse>(value)))
            {
                auto json = cacto::toJson(*ellipse);
                json["$type"] = "Ellipse";
                return std::move(json);
            }
            return nullptr;
        }

        Shared<Geometry> JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.getKind() == JsonValue::Object && json["$type"] == "Ellipse")
            {
                auto ellipse = std::make_shared<Ellipse>();
                cacto::fromJson(*ellipse, json);
                return std::move(ellipse);
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}