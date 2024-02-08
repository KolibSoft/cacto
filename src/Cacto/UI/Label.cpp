#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    Label &&Label::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Label &&Label::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Label &&Label::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Label &&Label::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Label &&Label::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Label &&Label::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Label &&Label::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Label &&Label::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    Label &&Label::setBackground(Node *const value)
    {
        Block::setBackground(value);
        return std::move(*this);
    }

    Label &&Label::setBackground(Node &&value)
    {
        Block::setBackground(std::move(value));
        return std::move(*this);
    }

    Label &&Label::setMargin(const Thickness &value)
    {
        Block::setMargin(value);
        return std::move(*this);
    }

    Label &&Label::setPadding(const Thickness &value)
    {
        Block::setPadding(value);
        return std::move(*this);
    }

    Label &&Label::setMinWidth(f32t value)
    {
        Block::setMinWidth(value);
        return std::move(*this);
    }

    Label &&Label::setMaxWidth(f32t value)
    {
        Block::setMaxWidth(value);
        return std::move(*this);
    }

    Label &&Label::setMinHeight(f32t value)
    {
        Block::setMinHeight(value);
        return std::move(*this);
    }

    Label &&Label::setMaxHeight(f32t value)
    {
        Block::setMaxHeight(value);
        return std::move(*this);
    }

    Label &&Label::setFixedWidth(f32t value)
    {
        Block::setFixedWidth(value);
        return std::move(*this);
    }

    Label &&Label::setFixedHeight(f32t value)
    {
        Block::setFixedHeight(value);
        return std::move(*this);
    }

    Label::operator const Span &() const
    {
        return m_span;
    }

    Label::operator Span &()
    {
        return m_span;
    }

    const sf::Font *const Label::getFont() const
    {
        return m_span.getFont();
    }

    Label &&Label::setFont(const sf::Font *const value)
    {
        m_span.setFont(value);
        return std::move(*this);
    }

    const sf::String &Label::getString() const
    {
        return m_span.getString();
    }

    Label &&Label::setString(const sf::String &value)
    {
        m_span.setString(value);
        return std::move(*this);
    }

    TextDirection Label::getDirection() const
    {
        return m_span.getDirection();
    }

    Label &&Label::setDirection(TextDirection value)
    {
        m_span.setDirection(value);
        return std::move(*this);
    }

    u32t Label::getCharacterSize() const
    {
        return m_span.getCharacterSize();
    }

    Label &&Label::setCharacterSize(u32t value)
    {
        m_span.setCharacterSize(value);
        return std::move(*this);
    }

    const sf::Color &Label::getColor() const
    {
        return m_span.getColor();
    }

    Label &&Label::setColor(const sf::Color &value)
    {
        m_span.setColor(value);
        return std::move(*this);
    }

    BoxAnchor Label::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    Label &&Label::setHorizontalAnchor(BoxAnchor value)
    {
        m_hAnchor = value;
        return std::move(*this);
    }

    BoxAnchor Label::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    Label &&Label::setVerticalAnchor(BoxAnchor value)
    {
        m_vAnchor = value;
        return std::move(*this);
    }

    Label &&Label::setId(const std::string &value)
    {
        Block::setId(value);
        return std::move(*this);
    }

    Label *Label::clone() const
    {
        auto label = new Label(*this);
        return label;
    }

    Label *Label::acquire()
    {
        auto label = new Label(std::move(*this));
        return label;
    }

    sf::Vector2f Label::compact()
    {
        auto contentSize = m_span.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Label::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        auto contentBox = getContentBox();
        m_span.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void Label::place(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        contentBox.setWidth(m_span.getWidth(), m_hAnchor);
        contentBox.setHeight(m_span.getHeight(), m_vAnchor);
        m_span.place({contentBox.getLeft(), contentBox.getTop()});
    }

    Label::Label()
        : Block(),
          m_span(),
          m_hAnchor(BoxAnchor::Start),
          m_vAnchor(BoxAnchor::Start)
    {
    }

    Label::~Label() = default;

    Label::Label(const Label &other)
        : Label()
    {
        *this = other;
    }

    Label &Label::operator=(const Label &other)
    {
        m_span = other.m_span;
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        Block::operator=(other);
        return *this;
    }

    Label::Label(Label &&other)
        : Label()
    {
        *this = std::move(other);
    }

    Label &Label::operator=(Label &&other)
    {
        m_span = std::move(other.m_span);
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        Block::operator=(std::move(other));
        return *this;
    }

    void Label::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(m_span, states);
    }

    XmlValue toXml(const Label &label)
    {
        XmlValue xml{"Label", {}};
        xml |= toXml((const Block &)label);
        xml |= toXml((const Span &)label);
        xml["direction"] = toString(label.getDirection());
        xml["horizontalAnchor"] = toString(label.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(label.getVerticalAnchor());
        return std::move(xml);
    }

    Label toLabel(const XmlValue &xml)
    {
        Label label{};
        (Block &)label = toBlock(xml);
        (Span &)label = toSpan(xml);
        label.setDirection(toTextDirection(xml.getAttribute("direction", "ToRight")));
        label.setHorizontalAnchor(toBoxAnchor(xml.getAttribute("horizontalAnchor", "Start")));
        label.setVerticalAnchor(toBoxAnchor(xml.getAttribute("verticalAnchor", "Start")));
        return std::move(label);
    }

    namespace label
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Label *label = nullptr;
            if (value && typeid(*value) == typeid(Label) && (label = dynamic_cast<const Label *>(value)))
            {
                auto xml = cacto::toXml(*label);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Label")
            {
                auto label = new Label();
                *label = toLabel(xml);
                return label;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}