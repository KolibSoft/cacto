#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Figure.hpp>

namespace cacto
{

    Figure::Scale Figure::getScale() const
    {
        return m_scale;
    }

    void Figure::setScale(Scale value)
    {
        m_scale = value;
        invalidate();
    }

    Figure::Figure(const sf::Texture &texture, Scale scale)
        : Surface(Rectangle.getGeometry(), sf::Color::White, &texture),
          m_scale(scale)
    {
    }

    Figure::~Figure() = default;

    Figure::Figure(const Figure &other)
        : Surface(other),
          m_scale(other.m_scale)
    {
    }

    Figure &Figure::operator=(const Figure &other)
    {
        Surface::operator=(other);
        m_scale = other.m_scale;
        return *this;
    }

    void Figure::onUpdate() const
    {
        auto &array = getArray();
        cacto::setPoints(array, getGeometry(), getPrecision());
        cacto::setColor(array, getColor());
        switch (m_scale)
        {
        case Fill:
        {
            cacto::setTexCoords(array, getTextureRect());
            cacto::mapPositions(array, {{getLeft(), getTop()}, {getWidth(), getHeight()}});
        }
        break;
        case Fit:
        {
            auto textureRect = getTextureRect();
            auto size = fitSize({textureRect.width, textureRect.height}, {getWidth(), getHeight()});
            Box box{*this};
            box.setWidth(size.x, Center);
            box.setHeight(size.y, Center);
            cacto::setTexCoords(array, textureRect);
            cacto::mapPositions(array, {{box.getLeft(), box.getTop()}, {box.getWidth(), box.getHeight()}});
        }
        break;
        case Crop:
            auto textureRect = getTextureRect();
            auto size = fitSize({getWidth(), getHeight()}, {textureRect.width, textureRect.height});
            Box box{textureRect.left, textureRect.top, textureRect.width, textureRect.height};
            box.setWidth(size.x, Center);
            box.setHeight(size.y, Center);
            cacto::setTexCoords(array, {{box.getLeft(), box.getTop()}, {box.getWidth(), box.getHeight()}});
            cacto::mapPositions(array, {{getLeft(), getTop()}, {getWidth(), getHeight()}});
            break;
        }
    }

}