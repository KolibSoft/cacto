#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/TextureUtils.hpp>
#include <Cacto/Graphics/GeometryUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/RectUtils.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    Surface &&Surface::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Surface &&Surface::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Surface &&Surface::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Surface &&Surface::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Surface &&Surface::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Surface &&Surface::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Surface &&Surface::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Surface &&Surface::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    const Geometry *const Surface::getGeometry() const
    {
        return m_geometry;
    }

    Surface &&Surface::setGeometry(const Geometry *const value)
    {
        m_geometry = value;
        m_invalid = true;
        return std::move(*this);
    }

    szt Surface::getPrecision() const
    {
        return m_precision;
    }

    Surface &&Surface::setPrecision(szt value)
    {
        if (value < 1)
            value = 1;
        m_precision = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::Color &Surface::getColor() const
    {
        return m_color;
    }

    Surface &&Surface::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::Texture *const Surface::getTexture() const
    {
        return m_texture;
    }

    Surface &&Surface::setTexture(const sf::Texture *const value, bool resetRect)
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
        return std::move(*this);
    }

    const sf::FloatRect &Surface::getTextureRect() const
    {
        return m_textureRect;
    }

    Surface &&Surface::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::Transform &Surface::getVisualTransform() const
    {
        return m_vTransform;
    }

    const std::string &Surface::getId() const
    {
        return m_id;
    }

    Surface &&Surface::setId(const std::string &value)
    {
        m_id = value;
        return std::move(*this);
    }

    Node *const Surface::getParent() const
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

    Surface *Surface::clone() const
    {
        auto surface = new Surface(*this);
        return surface;
    }

    Surface *Surface::acquire()
    {
        auto surface = new Surface(std::move(*this));
        return surface;
    }

    sf::Vector2f Surface::compact()
    {
        setWidth(0);
        setHeight(0);
        m_invalid = true;
        return {0, 0};
    }

    sf::Vector2f Surface::inflate(const sf::Vector2f &containerSize)
    {
        setWidth(containerSize.x);
        setHeight(containerSize.y);
        m_invalid = true;
        return containerSize;
    }

    void Surface::place(const sf::Vector2f &position)
    {
        setLeft(position.x);
        setTop(position.y);
        m_invalid = true;
    }

    bool Surface::containsVisualPoint(const sf::Vector2f &point) const
    {
        if (m_geometry)
        {
            auto surface = m_geometry->getBounds();
            auto _point = m_vTransform.getInverse().transformPoint(point);
            auto result = m_geometry->containsPoint(mapPoint(_point, *this, surface));
            return result;
        }
        return false;
    }

    Surface::Surface()
        : Box(),
          m_geometry(),
          m_precision(1),
          m_color(sf::Color::White),
          m_texture(),
          m_textureRect(),
          m_id(),
          m_parent(),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan),
          m_vTransform(sf::Transform::Identity)
    {
    }

    Surface::~Surface()
    {
        detach();
    }

    Surface::Surface(const Surface &other)
        : Surface()
    {
        *this = other;
    }

    Surface &Surface::operator=(const Surface &other)
    {
        Box::operator=(other);
        m_geometry = other.m_geometry;
        m_precision = other.m_precision;
        m_color = other.m_color;
        m_texture = other.m_texture;
        m_textureRect = other.m_textureRect;
        m_id = other.m_id;
        m_invalid = other.m_invalid;
        m_array = other.m_array;
        m_vTransform = other.m_vTransform;
        return *this;
    }

    Surface::Surface(Surface &&other)
        : Surface()
    {
        *this = std::move(other);
    }

    Surface &Surface::operator=(Surface &&other)
    {
        Box::operator=(std::move(other));
        m_geometry = other.m_geometry;
        m_precision = other.m_precision;
        m_color = std::move(other.m_color);
        m_texture = other.m_texture;
        m_textureRect = std::move(other.m_textureRect);
        m_id = std::move(other.m_id);
        m_invalid = other.m_invalid;
        m_array = std::move(other.m_array);
        m_vTransform = std::move(other.m_vTransform);
        other.m_geometry = nullptr;
        other.m_precision = 0;
        other.m_texture = nullptr;
        other.m_invalid = true;
        other.detach();
        return *this;
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
                cacto::mapPositions(m_array, *this);
                m_invalid = false;
            }
            if (getWidth() > 0 && getHeight() > 0)
            {
                auto _states = states;
                _states.texture = m_texture;
                target.draw(m_array, _states);
                m_vTransform = _states.transform;
            }
        }
    }

    XmlValue toXml(const Surface &surface)
    {
        XmlValue xml{"Surface", {}};
        xml["geometry"] = getExpression(surface.getGeometry());
        xml["precision"] = std::to_string(surface.getPrecision());
        xml["color"] = getExpression(surface.getColor());
        xml["texture"] = getExpression(surface.getTexture());
        xml["textureRect"] = toString(surface.getTextureRect());
        xml["id"] = surface.getId();
        return std::move(xml);
    }

    Surface toSurface(const XmlValue &xml)
    {
        Surface surface{};
        surface.setGeometry(getGeometry(xml.getAttribute("geometry")));
        surface.setPrecision(std::stoi(xml.getAttribute("precision", "1")));
        surface.setColor(getColor(xml.getAttribute("color", "#FFFFFFFF")));
        surface.setTexture(getTexture(xml.getAttribute("texture")));
        surface.setTextureRect(toRect(xml.getAttribute("textureRect", "0,0,0,0")));
        surface.setId(xml.getAttribute("id"));
        return std::move(surface);
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
                *surface = toSurface(xml);
                return surface;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}