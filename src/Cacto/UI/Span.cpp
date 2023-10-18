#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Span.hpp>

namespace cacto
{

    Node *const Span::getParent() const
    {
        return m_parent;
    }

    Span::Span(const sf::Font &font, const sf::String &string, u32t characterSize)
        : sf::Text(font, string, characterSize),
          m_parent()
    {
    }

    Span::~Span()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

    Span::Span(const Span &other)
        : sf::Text(other),
          m_parent()
    {
    }

    Span &Span::operator=(const Span &other)
    {
        sf::Text::operator=(other);
        return *this;
    }

    void Span::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Span::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Span::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto *text = dynamic_cast<const sf::Text *>(this);
        target.draw(*text, states);
    }

    sf::Vector2f Span::onCompact(const sf::Vector2f &contentSize)
    {
        auto bounds = getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    sf::Vector2f Span::onInflate(const sf::Vector2f &containerSize)
    {
        auto bounds = getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    void Span::onPlace(const sf::Vector2f &position)
    {
        auto bounds = getLocalBounds();
        auto _position = position - sf::Vector2f{bounds.left, bounds.top};
        setPosition(_position);
    }

}