#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Core/StringUtils.hpp>
#include <Cacto/Graphics/FontUtils.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/UI/Span.hpp>

namespace cacto
{

    Span &&Span::setOrigin(const sf::Vector2f &value)
    {
        sf::Transformable::setOrigin(value);
        return std::move(*this);
    }

    Span &&Span::setPosition(const sf::Vector2f &value)
    {
        sf::Transformable::setPosition(value);
        return std::move(*this);
    }

    Span &&Span::setScale(const sf::Vector2f &value)
    {
        sf::Transformable::setScale(value);
        return std::move(*this);
    }

    Span &&Span::setRotation(sf::Angle value)
    {
        sf::Transformable::setRotation(value);
        return std::move(*this);
    }

    Span &&Span::move(const sf::Vector2f &offset)
    {
        sf::Transformable::move(offset);
        return std::move(*this);
    }

    Span &&Span::scale(const sf::Vector2f &factors)
    {
        sf::Transformable::scale(factors);
        return std::move(*this);
    }

    Span &&Span::rotate(const sf::Angle &angle)
    {
        sf::Transformable::rotate(angle);
        return std::move(*this);
    }

    Span::operator const Box &() const
    {
        return m_box;
    }

    const sf::Font *const Span::getFont() const
    {
        return m_font;
    }

    Span &&Span::setFont(const sf::Font *const value)
    {
        m_font = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::String &Span::getString() const
    {
        return m_string;
    }

    Span &&Span::setString(const sf::String &value)
    {
        m_string = value;
        m_invalid = true;
        return std::move(*this);
    }

    TextDirection Span::getDirection() const
    {
        return m_direction;
    }

    Span &&Span::setDirection(TextDirection value)
    {
        m_direction = value;
        m_invalid = true;
        return std::move(*this);
    }

    u32t Span::getCharacterSize() const
    {
        return m_characterSize;
    }

    Span &&Span::setCharacterSize(u32t value)
    {
        m_characterSize = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::Color &Span::getColor() const
    {
        return m_color;
    }

    Span &&Span::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
        return std::move(*this);
    }

    const sf::Transform &Span::getVisualTransform() const
    {
        return m_vTransform;
    }

    const std::string &Span::getId() const
    {
        return m_id;
    }

    Span &&Span::setId(const std::string &value)
    {
        m_id = value;
        return std::move(*this);
    }

    Node *const Span::getParent() const
    {
        return m_parent;
    }

    void Span::attach(ParentNode &parent)
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

    void Span::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    Span *Span::clone() const
    {
        auto span = new Span(*this);
        return span;
    }

    Span *Span::acquire()
    {
        auto span = new Span(std::move(*this));
        return span;
    }

    void Span::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_font && m_characterSize)
        {
            if (m_invalid)
            {
                cacto::setGlyphs(m_array, m_string, m_direction, *m_font, m_characterSize, false, 0);
                cacto::setColor(m_array, m_color);
                m_invalid = false;
            }
            auto _states = states;
            _states.transform.translate({m_box.getLeft(), m_box.getTop()});
            _states.texture = &m_font->getTexture(m_characterSize);
            target.draw(m_array, _states);
            m_vTransform = _states.transform;
        }
    }

    sf::Vector2f Span::compact()
    {
        auto bounds = m_array.getBounds();
        m_box.setWidth(bounds.width);
        m_box.setHeight(bounds.height);
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    sf::Vector2f Span::inflate(const sf::Vector2f &containerSize)
    {
        auto bounds = m_array.getBounds();
        m_box.setWidth(bounds.width);
        m_box.setHeight(bounds.height);
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    void Span::place(const sf::Vector2f &position)
    {
        auto bounds = m_array.getBounds();
        m_box.setLeft(position.x - bounds.left);
        m_box.setTop(position.y - bounds.top);
    }

    bool Span::containsVisualPoint(const sf::Vector2f &point) const
    {
        auto result = m_box.containsPoint(m_vTransform.getInverse().transformPoint(point));
        return result;
    }

    Span::Span()
        : sf::Transformable(),
          m_box(),
          m_font(),
          m_string(),
          m_direction(TextDirection::ToRight),
          m_characterSize(),
          m_color(sf::Color::White),
          m_id(),
          m_parent(),
          m_invalid(true),
          m_array(sf::PrimitiveType::Triangles),
          m_vTransform(sf::Transform::Identity)
    {
    }

    Span::~Span()
    {
        detach();
    }

    Span::Span(const Span &other)
        : Span()
    {
        *this = other;
    }

    Span &Span::operator=(const Span &other)
    {
        sf::Transformable::operator=(other);
        m_box = other.m_box;
        m_font = other.m_font;
        m_string = other.m_string;
        m_direction = other.m_direction;
        m_characterSize = other.m_characterSize;
        m_color = other.m_color;
        m_id = other.m_id;
        m_invalid = other.m_invalid;
        m_array = other.m_array;
        m_vTransform = other.m_vTransform;
        return *this;
    }

    Span::Span(Span &&other)
        : Span()
    {
        *this = std::move(other);
    }

    Span &Span::operator=(Span &&other)
    {
        sf::Transformable::operator=(std::move(other));
        m_box = std::move(other.m_box);
        m_font = other.m_font;
        m_string = std::move(other.m_string);
        m_direction = other.m_direction;
        m_characterSize = other.m_characterSize;
        m_color = std::move(other.m_color);
        m_id = std::move(other.m_id);
        m_invalid = other.m_invalid;
        m_array = std::move(other.m_array);
        m_vTransform = std::move(other.m_vTransform);
        other.m_font = nullptr;
        other.m_characterSize = 0;
        other.m_invalid = true;
        other.detach();
        return *this;
    }

    XmlValue toXml(const Span &span)
    {
        XmlValue xml{"Span", {}};
        xml["id"] = span.getId();
        xml["font"] = getExpression(span.getFont());
        xml["string"] = getExpression(span.getString());
        xml["direction"] = toString(span.getDirection());
        xml["characterSize"] = std::to_string(span.getCharacterSize());
        xml["color"] = getExpression(span.getColor());
        return std::move(xml);
    }

    Span toSpan(const XmlValue &xml)
    {
        Span span{};
        span.setId(xml.getAttribute("id"));
        span.setFont(getFont(xml.getAttribute("font")));
        span.setString(getString(xml.getAttribute("string")));
        span.setColor(getColor(xml.getAttribute("color", "#FFFFFFFF")));
        span.setDirection(toTextDirection(xml.getAttribute("direction", "ToRight")));
        span.setCharacterSize(std::stoi(xml.getAttribute("characterSize", "0")));
        return std::move(span);
    }

    namespace span
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Span *span = nullptr;
            if (value && typeid(*value) == typeid(Span) && (span = dynamic_cast<const Span *>(value)))
            {
                auto xml = cacto::toXml(*span);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Span")
            {
                auto span = new Span();
                *span = toSpan(xml);
                return span;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}