#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    const std::string &Surface::getTag() const
    {
        return m_tag;
    }

    void Surface::setTag(const std::string &value)
    {
        m_tag = value;
    }

    Node *const Surface::getParent() const
    {
        return m_parent;
    }

    const Geometry &Surface::getGeometry() const
    {
        return *m_geometry;
    }

    Surface &Surface::setGeometry(const Geometry &value)
    {
        m_geometry = &value;
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

    const sf::Texture *const Surface::getTexture() const
    {
        return m_texture;
    }

    Surface &Surface::setTexture(const sf::Texture *const value, bool resetRect)
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

    Surface::Surface(const Geometry &geometry, const sf::Color &color, const sf::Texture *texture)
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
        Surface surface{};
        surface.setColor(color);
        return surface;
    }

    Surface textureSurface(const sf::Texture &texture, const sf::FloatRect &textureRect)
    {
        Surface surface{};
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

    XmlValue toXml(const Surface &surface)
    {
        XmlValue xml{"Surface", {}};
        xml["tag"] = surface.getTag();
        auto &geometry = surface.getGeometry();
        if (typeid(geometry) == typeid(Rectangle))
            xml["geometry"] = "Rectangle";
        else if (typeid(geometry) == typeid(Ellipse))
            xml["geometry"] = "Ellipse";
        else
            throw std::runtime_error("Not supported geometry");
        xml["precision"] = std::to_string(surface.getPrecision());
        xml["color"] = toString(surface.getColor());
        auto texture = surface.getTexture();
        if (texture)
        {
            auto id = getId(*texture);
            if (id)
                xml["texture"] = *id;
        }
        xml["textureRect"] = toString(surface.getTextureRect());
        return std::move(xml);
    }

    void fromXml(Surface &surface, const XmlValue &xml)
    {
        surface = {};
        surface.setTag(xml.getAttribute("tag"));
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
        auto id = xml.getAttribute("texture");
        if (id.size())
        {
            auto texture = getTexture(id);
            if (texture)
                surface.setTexture(texture);
        }
        sf::FloatRect rect{};
        cacto::fromString(rect, xml.getAttribute("textureRect", "0,0,0,0"));
        surface.setTextureRect(rect);
    }

    namespace surface
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Surface *surface = nullptr;
            if (value && typeid(*value) == typeid(Surface) && (surface = dynamic_cast<const Surface *>(value)))
            {
                auto xml = cacto::toXml(*surface);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Surface")
            {
                auto surface = new Surface();
                cacto::fromXml(*surface, xml);
                return surface;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}