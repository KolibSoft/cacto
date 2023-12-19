#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    const std::string &Surface::getId() const
    {
        return m_id;
    }

    Surface &Surface::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    Shared<Node> Surface::getParent() const
    {
        return m_parent.lock();
    }

    const Shared<const Geometry> &Surface::getGeometry() const
    {
        return m_geometry;
    }

    Surface &Surface::setGeometry(const Shared<const Geometry> &value)
    {
        m_geometry = value;
        m_invalid = true;
        return *this;
    }

    szt Surface::getPrecision() const
    {
        return m_precision;
    }

    Surface &Surface::setPrecision(szt value)
    {
        if (value < 1)
            value = 1;
        m_precision = value;
        m_invalid = true;
        return *this;
    }

    const sf::Color &Surface::getColor() const
    {
        return m_color;
    }

    Surface &Surface::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
        return *this;
    }

    const Shared<const sf::Texture> &Surface::getTexture() const
    {
        return m_texture;
    }

    Surface &Surface::setTexture(const Shared<const sf::Texture> &value, bool resetRect)
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
        return *this;
    }

    const sf::FloatRect &Surface::getTextureRect() const
    {
        return m_textureRect;
    }

    Surface &Surface::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        m_invalid = true;
        return *this;
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
        : m_id(),
          m_parent(),
          m_geometry(),
          m_precision(1),
          m_color(),
          m_texture(),
          m_textureRect(),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
        if (m_texture)
            setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
    }

    Surface::~Surface() = default;

    sf::VertexArray &Surface::getArray() const
    {
        return m_array;
    }

    void Surface::invalidate()
    {
        m_invalid = true;
    }

    void Surface::onAttach(const Shared<Node> &parent)
    {
        m_parent = parent;
    }

    void Surface::onDetach(const Shared<Node> &parent)
    {
        m_parent.reset();
    }

    void Surface::onUpdate() const
    {
        if (m_geometry)
        {
            cacto::setPoints(m_array, *m_geometry, m_precision);
            cacto::setColor(m_array, m_color);
            if (m_texture)
                cacto::setTexCoords(m_array, m_textureRect);
            cacto::mapPositions(m_array, *this);
        }
    }

    void Surface::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_geometry)
        {
            update();
            if (getWidth() > 0 && getHeight() > 0)
            {
                auto _states = states;
                _states.texture = m_texture.get();
                target.draw(m_array, _states);
            }
            DrawNode::onDraw(target, states);
        }
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

    XmlValue toXml(const Surface &surface)
    {
        XmlValue xml{"Surface", {}};
        xml["id"] = surface.getId();
        auto &geometry = surface.getGeometry();
        if (typeid(geometry) == typeid(Rectangle))
            xml["geometry"] = "Rectangle";
        else if (typeid(geometry) == typeid(Ellipse))
            xml["geometry"] = "Ellipse";
        else
            throw std::runtime_error("Not supported geometry");
        xml["precision"] = std::to_string(surface.getPrecision());
        xml["color"] = toString(surface.getColor());
        xml["texture"] = Pack<sf::Texture>::id(surface.getTexture());
        xml["textureRect"] = toString(surface.getTextureRect());
        return std::move(xml);
    }

    void fromXml(Surface &surface, const XmlValue &xml)
    {
        surface.setId(xml.getAttribute("id"));
        auto geometry = xml.getAttribute("geometry", "Rectangle");
        if (geometry == "Rectangle")
            surface.setGeometry(Rectangle::Identity);
        else if (geometry == "Ellipse")
            surface.setGeometry(Ellipse::Identity);
        else
            throw std::runtime_error("Not supported geometry");
        surface.setPrecision(std::stoi(xml.getAttribute("precision", "0")));
        sf::Color color{};
        cacto::fromString(color, xml.getAttribute("color", "#FFFFFFFF"));
        surface.setColor(color);
        surface.setTexture(Pack<sf::Texture>::resource(xml.getAttribute("texture")));
        sf::FloatRect rect{};
        cacto::fromString(rect, xml.getAttribute("textureRect", "0,0,0,0"));
        surface.setTextureRect(rect);
    }

    namespace surface
    {

        XmlValue XmlConverter::toXml(const Shared<const Node> &value) const
        {
            Shared<const Surface> surface = nullptr;
            auto ptr = value.get();
            if (value && typeid(*ptr) == typeid(Surface) && (surface = std::dynamic_pointer_cast<const Surface>(value)))
            {
                auto xml = cacto::toXml(*surface);
                return std::move(xml);
            }
            return nullptr;
        }

        Shared<Node> XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Surface")
            {
                auto surface = std::make_shared<Surface>();
                cacto::fromXml(*surface, xml);
                return std::move(surface);
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}