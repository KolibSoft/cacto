#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    Node *const Surface::getParent() const
    {
        return m_parent;
    }

    const SharedGeometry &Surface::getGeometry() const
    {
        return m_geometry;
    }

    void Surface::setGeometry(const SharedGeometry &value)
    {
        m_geometry = value;
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

    const SharedTexture &Surface::getTexture() const
    {
        return m_texutre;
    }

    void Surface::setTexture(const SharedTexture &value)
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

    Surface::Surface()
        : m_parent(nullptr),
          m_geometry(new Rectangle({0, 0}, {1, 1})),
          m_precision(1),
          m_color(sf::Color::White),
          m_texutre(nullptr),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
    }

    Surface::~Surface() = default;

    void Surface::onAttach(Node &parent)
    {
        Node::onAttach(parent);
        m_parent = &parent;
    }

    void Surface::onDetach(Node &parent)
    {
        Node::onDetach(parent);
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

    bool Surface::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update();
        if (getWidth() > 0 && getHeight() > 0)
        {
            auto _states = states;
            _states.texture = m_texutre.get();
            target.draw(m_array, _states);
        }
        return false;
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

    SharedSurface makeColorSurface(const sf::Color &color, const SharedGeometry &geometry, szt precision)
    {
        auto surface = std::make_shared<Surface>();
        surface->setColor(color);
        if (geometry)
            surface->setGeometry(geometry);
        surface->setPrecision(precision);
        return surface;
    }

    SharedSurface makeTextureSurface(const SharedTexture &texture, const SharedGeometry &geometry, szt precision)
    {
        auto surface = std::make_shared<Surface>();
        surface->setTexture(texture);
        if (geometry)
            surface->setGeometry(geometry);
        surface->setPrecision(precision);
        return surface;
    }

}