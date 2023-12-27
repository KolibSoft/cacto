#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
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

    const Geometry *const Surface::getGeometry() const
    {
        return m_geometry;
    }

    Surface &Surface::setGeometry(const Geometry *const value)
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

    const Box &Surface::asBox() const
    {
        return m_box;
    }

    Box &Surface::asBox()
    {
        return m_box;
    }

    ParentNode *const Surface::getParent() const
    {
        return m_parent;
    }

    void Surface::attach(ParentNode &parent)
    {
        if (m_parent == &parent)
            return;
        if (m_parent != nullptr)
            throw std::runtime_error("This node is already attached to another parent");
        if (parent.hasAncestor(*this))
            throw std::runtime_error("This node is an ancestor");
        m_parent = &parent;
        parent.append(*this);
    }

    void Surface::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    void Surface::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_geometry)
        {
            if (m_invalid)
            {
                cacto::setPoints(m_array, *m_geometry, m_precision);
                cacto::setColor(m_array, m_color);
                if (m_texture)
                    cacto::setTexCoords(m_array, m_textureRect);
                cacto::mapPositions(m_array, m_box);
                m_invalid = false;
            }
            if (m_box.getWidth() > 0 && m_box.getHeight() > 0)
            {
                auto _states = states;
                _states.texture = m_texture;
                target.draw(m_array, _states);
            }
        }
    }

    sf::Vector2f Surface::compact()
    {
        m_box.setWidth(0);
        m_box.setHeight(0);
        m_invalid = true;
        return {0, 0};
    }

    sf::Vector2f Surface::inflate(const sf::Vector2f &containerSize)
    {
        m_box.setWidth(containerSize.x);
        m_box.setHeight(containerSize.y);
        m_invalid = true;
        return containerSize;
    }

    void Surface::place(const sf::Vector2f &position)
    {
        m_box.setLeft(position.x);
        m_box.setTop(position.y);
        m_invalid = true;
    }

    Surface::Surface()
        : m_id(),
          m_box(),
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

    Surface::~Surface()
    {
        detach();
    }

    XmlValue toXml(const Surface &surface)
    {
        XmlValue xml{"Surface", {}};
        auto &id = surface.getId();
        auto geometry = surface.getGeometry();
        auto precision = surface.getPrecision();
        auto color = surface.getColor();
        auto texture = surface.getTexture();
        auto textureRect = surface.getTextureRect();
        xml["id"] = id;
        xml["geometry"] = geometry ? getId(*geometry) : "";
        xml["precision"] = std::to_string(precision);
        xml["color"] = toString(color);
        xml["texture"] = texture ? getId(*texture) : "";
        xml["textureRect"] = toString(textureRect);
        return std::move(xml);
    }

    void fromXml(Surface &surface, const XmlValue &xml)
    {
        surface.setId(xml.getAttribute("id"));
        auto geometry = getGeometry(xml.getAttribute("geometry"));
        szt precision = std::stoi(xml.getAttribute("precision", "1"));
        sf::Color color{};
        auto texture = getTexture(xml.getAttribute("texture"));
        sf::FloatRect textureRect{};
        cacto::fromString(color, xml.getAttribute("color", "#FFFFFFFF"));
        cacto::fromString(textureRect, xml.getAttribute("textureRect", "0,0,0,0"));
        surface.setGeometry(geometry);
        surface.setPrecision(precision);
        surface.setColor(color);
        surface.setTexture(texture);
        surface.setTextureRect(textureRect);
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
                auto surface = std::make_shared<Surface>();
                cacto::fromXml(*surface, xml);
                Node::XmlStack.push(surface);
                return surface.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}