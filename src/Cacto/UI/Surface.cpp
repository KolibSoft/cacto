#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    Node *const Surface::getParent() const
    {
        return m_parent;
    }

    Geometry &Surface::getGeometry() const
    {
        return *m_geometry;
    }

    void Surface::setGeometry(Geometry &value)
    {
        m_geometry = &value;
        m_invalid = true;
    }

    szt Surface::getPrecision() const
    {
        return m_precision;
    }

    void Surface::setPrecision(szt value)
    {
        if (value < 1)
            value = 1;
        m_precision = value;
        m_invalid = true;
    }

    const sf::Color &Surface::getColor() const
    {
        return m_color;
    }

    void Surface::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
    }

    const sf::Texture *const Surface::getTexture() const
    {
        return m_texture;
    }

    void Surface::setTexture(const sf::Texture *const value, bool resetRect)
    {
        m_texture = value;
        m_invalid = true;
        if (resetRect)
        {
            if (value)
                setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
            else
                setTextureRect({{0, 0}, {0, 0}});
        }
    }

    const sf::FloatRect &Surface::getTextureRect() const
    {
        return m_textureRect;
    }

    void Surface::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        m_invalid = true;
    }

    void Surface::update(bool force) const
    {
        if (m_invalid || force)
        {
            onUpdate();
            m_invalid = false;
        }
    }

    Surface::Surface(Geometry &geometry, const sf::Color &color, const sf::Texture *texture)
        : m_parent(),
          m_geometry(&geometry),
          m_precision(1),
          m_color(color),
          m_texture(texture),
          m_textureRect(),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
        if (m_texture)
            setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
    }

    Surface::~Surface()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

    Surface::Surface(const Surface &other)
        : m_parent(),
          m_geometry(other.m_geometry),
          m_precision(other.m_precision),
          m_color(other.m_color),
          m_texture(other.m_texture),
          m_textureRect(other.m_textureRect),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
    }

    Surface &Surface::operator=(const Surface &other)
    {
        m_geometry = other.m_geometry;
        m_precision = other.m_precision;
        m_color = other.m_color;
        m_texture = other.m_texture;
        m_textureRect = other.m_textureRect;
        m_invalid = true;
        m_array = sf::VertexArray{sf::PrimitiveType::TriangleFan};
        return *this;
    }

    const Surface Surface::Rectangle{Rectangle::Identity};

    const Surface Surface::Ellipse{Ellipse::Identity};

    sf::VertexArray &Surface::getArray() const
    {
        return m_array;
    }

    void Surface::invalidate()
    {
        m_invalid = true;
    }

    void Surface::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Surface::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Surface::onUpdate() const
    {
        cacto::setPoints(m_array, *m_geometry, m_precision);
        cacto::setColor(m_array, m_color);
        if (m_texture)
            cacto::setTexCoords(m_array, m_textureRect);
        cacto::mapPositions(m_array, *this);
    }

    void Surface::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update();
        if (getWidth() > 0 && getHeight() > 0)
        {
            auto _states = states;
            _states.texture = m_texture;
            target.draw(m_array, _states);
        }
        DrawNode::onDraw(target, states);
    }

    sf::Vector2f Surface::onCompact()
    {
        setWidth(0);
        setHeight(0);
        m_invalid = true;
        return {0, 0};
    }

    sf::Vector2f Surface::onInflate(const sf::Vector2f &containerSize)
    {
        setWidth(containerSize.x);
        setHeight(containerSize.y);
        m_invalid = true;
        return containerSize;
    }

    void Surface::onPlace(const sf::Vector2f &position)
    {
        setLeft(position.x);
        setTop(position.y);
        m_invalid = true;
    }

    Surface colorSurface(const sf::Color &color)
    {
        auto surface = Surface::Rectangle;
        surface.setColor(color);
        return surface;
    }

    Surface textureSurface(const sf::Texture &texture, const sf::FloatRect &textureRect)
    {
        auto surface = Surface::Rectangle;
        if (textureRect == sf::FloatRect{})
        {
            surface.setTexture(&texture, true);
        }
        else
        {
            surface.setTexture(&texture, false);
            surface.setTextureRect(textureRect);
        }
        return surface;
    }

}