#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    const Span &Label::getSpan() const
    {
        return m_span;
    }

    Span &Label::getSpan()
    {
        return m_span;
    }

    Label::Anchor Label::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void Label::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    Label::Anchor Label::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void Label::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    Label::Label(const sf::Font &font, const sf::String &string, u32t characterSize)
        : Block(),
          m_span(font, string, characterSize),
          m_hAnchor(Start),
          m_vAnchor(Start)
    {
    }

    Label::~Label() = default;

    Label::Label(const Label &other)
        : Block(other),
          m_span(other.m_span),
          m_hAnchor(other.m_hAnchor),
          m_vAnchor(other.m_vAnchor)
    {
    }

    Label &Label::operator=(const Label &other)
    {
        m_span = other.m_span;
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        return *this;
    }

    void Label::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(dynamic_cast<const DrawNode &>(m_span), states);
    }

    sf::Vector2f Label::onCompact()
    {
        auto contentSize = m_span.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Label::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        auto contentBox = getContentBox();
        m_span.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void Label::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        auto bounds = m_span.getLocalBounds();
        contentBox.setWidth(bounds.width, m_hAnchor);
        contentBox.setHeight(bounds.height, m_vAnchor);
        m_span.place({contentBox.getLeft(), contentBox.getTop()});
    }

}