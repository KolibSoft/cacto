#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Span.hpp>

namespace cacto
{

    const Shared<const sf::Font> &Span::getFont() const
    {
        return m_font;
    }

    void Span::setFont(const Shared<const sf::Font> &value)
    {
        m_font = value;
        if (m_font)
            sf::Text::setFont(*m_font);
    }

    Shared<Node> Span::getParent() const
    {
        return m_parent.lock();
    }

    Span::Span()
        : sf::Text(NoFont),
          m_place(),
          m_parent()
    {
    }

    Span::~Span() = default;

    const sf::Font Span::NoFont{};

    void Span::onAttach(const Shared<Node> &parent)
    {
        m_parent = parent;
    }

    void Span::onDetach(const Shared<Node> &parent)
    {
        m_parent.reset();
    }

    void Span::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_font)
        {
            auto *text = dynamic_cast<const sf::Text *>(this);
            auto _states = states;
            _states.transform.translate(m_place);
            target.draw(*text, _states);
        }
    }

    sf::Vector2f Span::onCompact()
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
        m_place = {position.x - bounds.left, position.y - bounds.top};
    }

}