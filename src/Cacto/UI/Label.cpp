#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    Node *const Label::getParent() const
    {
        auto parent = m_frame.getParent();
        return parent;
    }

    const Block &Label::getBlock() const
    {
        return m_frame;
    }

    Block &Label::getBlock()
    {
        return m_frame;
    }

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
        auto anchor = m_frame.getHorizontalAnchor(m_span);
        return anchor;
    }

    void Label::setHorizontalAnchor(Anchor value)
    {
        m_frame.setHorizontalAnchor(m_span, value);
    }

    Label::Anchor Label::getVerticalAnchor() const
    {
        auto anchor = m_frame.getVerticalAnchor(m_span);
        return anchor;
    }

    void Label::setVerticalAnchor(Anchor value)
    {
        m_frame.setVerticalAnchor(m_span, value);
    }

    Label::Label(const sf::Font &font, const sf::String &string, u32t characterSize)
        : m_parent(),
          m_frame(),
          m_span(font, string, characterSize)
    {
        m_frame.append(m_span);
    }

    Label::~Label() {}

    Label::Label(const Label &other)
        : m_parent(),
          m_frame(other.m_frame),
          m_span(other.m_span)
    {
        m_frame.append(m_span);
    }

    Label &Label::operator=(const Label &other)
    {
        m_frame = other.m_frame;
        m_span = other.m_span;
        return *this;
    }

    void Label::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Label::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Label::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(m_frame, states);
    }

    sf::Vector2f Label::onCompact(const sf::Vector2f &contentSize)
    {
        auto size = m_frame.compact(contentSize);
        return size;
    }

    sf::Vector2f Label::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = m_frame.inflate(containerSize);
        return size;
    }

    void Label::onPlace(const sf::Vector2f &position)
    {
        m_frame.place(position);
    }

}