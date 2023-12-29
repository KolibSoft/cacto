#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Cacto/Core/StringUtils.hpp>
#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/UI/Span.hpp>

namespace cacto
{

    const std::string &Span::getId() const
    {
        return m_id;
    }

    Span &Span::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    const sf::Font *const Span::getFont() const
    {
        return m_font;
    }

    Span &Span::setFont(const sf::Font *const value)
    {
        m_font = value;
        m_invalid = true;
        return *this;
    }

    const sf::String &Span::getString() const
    {
        return m_string;
    }

    Span &Span::setString(const sf::String &value)
    {
        m_string = value;
        m_invalid = true;
        return *this;
    }

    Span::Direction Span::getDirection() const
    {
        return m_direction;
    }

    Span &Span::setDirection(Direction value)
    {
        m_direction = value;
        m_invalid = true;
        return *this;
    }

    u32t Span::getCharacterSize() const
    {
        return m_characterSize;
    }

    Span &Span::setCharacterSize(u32t value)
    {
        m_characterSize = value;
        m_invalid = true;
        return *this;
    }

    const sf::Color &Span::getColor() const
    {
        return m_color;
    }

    Span &Span::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
        return *this;
    }

    ParentNode *const Span::getParent() const
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

    void Span::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_font && m_characterSize)
        {
            if (m_invalid)
            {
                cacto::setGlyphs(m_array, *m_font, m_string, m_direction, m_characterSize, false, 0);
                cacto::setColor(m_array, m_color);
                m_invalid = false;
            }
            auto _states = states;
            _states.transform.translate({getLeft(), getTop()});
            _states.texture = &m_font->getTexture(m_characterSize);
            target.draw(m_array, _states);
            m_vTransform = _states.transform;
        }
    }

    sf::Vector2f Span::compact()
    {
        auto bounds = m_array.getBounds();
        setWidth(bounds.width);
        setHeight(bounds.height);
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    sf::Vector2f Span::inflate(const sf::Vector2f &containerSize)
    {
        auto bounds = m_array.getBounds();
        setWidth(bounds.width);
        setHeight(bounds.height);
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    void Span::place(const sf::Vector2f &position)
    {
        auto bounds = m_array.getBounds();
        setLeft(position.x - bounds.left);
        setTop(position.y - bounds.top);
    }

    bool Span::containsVisualPoint(const sf::Vector2f &point) const
    {
        auto result = containsPoint(m_vTransform.getInverse().transformPoint(point));
        return result;
    }

    Span::Span()
        : Box(),
          m_id(),
          m_font(),
          m_string(),
          m_direction(Direction::ToRight),
          m_characterSize(),
          m_color(sf::Color::White),
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

    XmlValue toXml(const Span &span)
    {
        XmlValue xml{"Span", {}};
        auto font = span.getFont();
        auto color = getId(span.getColor());
        xml["id"] = span.getId();
        xml["font"] = font ? getId(*font) : "";
        xml["string"] = toAttribute(span.getString());
        xml["direction"] = toString(span.getDirection());
        xml["characterSize"] = std::to_string(span.getCharacterSize());
        xml["color"] = color.size() ? color : toString(span.getColor());
        return std::move(xml);
    }

    void fromXml(Span &span, const XmlValue &xml)
    {
        auto id = xml.getAttribute("id");
        auto font = getFont(xml.getAttribute("font"));
        sf::String string{};
        sf::Color color{};
        TextDirection direction{};
        u32t characterSize = std::stoi(xml.getAttribute("characterSize", "0"));
        cacto::fromAttribute(string, xml.getAttribute("string"));
        cacto::fromAttribute(color, xml.getAttribute("color", "#FFFFFFFF"));
        cacto::fromString(direction, xml.getAttribute("direction", "ToRight"));
        span
            .setId(id)
            .setFont(font)
            .setString(string)
            .setDirection(direction)
            .setCharacterSize(characterSize)
            .setColor(color);
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
                auto span = std::make_shared<Span>();
                cacto::fromXml(*span, xml);
                Node::XmlStack.push(span);
                return span.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}