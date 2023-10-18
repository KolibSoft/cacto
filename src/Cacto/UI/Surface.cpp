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
        return m_texutre;
    }

    void Surface::setTexture(const sf::Texture *const value)
    {
        m_texutre = value;
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

    Surface::Surface(Geometry &geometry, szt precision, const sf::Color &color, sf::Texture *texture)
        : m_parent(),
          m_geometry(&geometry),
          m_precision(precision),
          m_color(color),
          m_texutre(texture),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
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
          m_texutre(other.m_texutre),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
    }

    Surface &Surface::operator=(const Surface &other)
    {
        m_geometry = other.m_geometry;
        m_precision = other.m_precision;
        m_color = other.m_color;
        m_texutre = other.m_texutre;
        m_invalid = true;
        m_array = sf::VertexArray{sf::PrimitiveType::TriangleFan};
        return *this;
    }

    const Surface Surface::Rectangle{Rectangle::Identity};

    const Surface Surface::Ellipse{Ellipse::Identity};

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
        if (m_geometry)
            cacto::setPoints(m_array, *m_geometry, m_precision);
        cacto::setColor(m_array, m_color);
        if (m_texutre)
            cacto::setTexCoords(m_array, {{0, 0}, sf::Vector2f(m_texutre->getSize())});
        cacto::mapPositions(m_array, {{getLeft(), getTop()}, {getWidth(), getHeight()}});
    }

    void Surface::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update();
        if (getWidth() > 0 && getHeight() > 0)
        {
            auto _states = states;
            _states.texture = m_texutre;
            target.draw(m_array, _states);
        }
        DrawNode::onDraw(target, states);
    }

    sf::Vector2f Surface::onCompact(const sf::Vector2f &contentSize)
    {
        setWidth(contentSize.x);
        setHeight(contentSize.y);
        m_invalid = true;
        return contentSize;
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

    Surface colorSurface(const sf::Color &color, Geometry &geometry, szt precision)
    {
        Surface surface{geometry};
        surface.setColor(color);
        surface.setPrecision(precision);
        return surface;
    }

    Surface textureSurface(sf::Texture &texture, Geometry &geometry, szt precision)
    {
        Surface surface{geometry};
        surface.setTexture(&texture);
        surface.setPrecision(precision);
        return surface;
    }

}