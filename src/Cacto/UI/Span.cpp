#include <SFML/Graphics/RenderTarget.hpp>
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

    const Shared<const sf::Font> &Span::getFont() const
    {
        return m_font;
    }

    Span &Span::setFont(const Shared<const sf::Font> &value)
    {
        m_font = value;
        if (m_font)
            m_text.setFont(*m_font);
        return *this;
    }

    const Shared<const sf::String> &Span::getString() const
    {
        return m_string;
    }

    Span &Span::setString(const Shared<const sf::String> &value)
    {
        m_string = value;
        if (m_string)
            m_text.setString(*m_string);
        return *this;
    }

    const sf::Text &Span::asText() const
    {
        return m_text;
    }

    sf::Text &Span::asText()
    {
        return m_text;
    }

    Shared<Node> Span::getParent() const
    {
        return m_parent.lock();
    }

    Span::Span()
        : m_id(),
          m_font(),
          m_string(),
          m_text(*Pack<sf::Font>::resource("Default")),
          m_place(),
          m_parent()
    {
    }

    Span::~Span() = default;

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
        if (m_font && m_string)
        {
            auto _states = states;
            _states.transform.translate(m_place);
            target.draw(m_text, _states);
        }
    }

    sf::Vector2f Span::onCompact()
    {
        auto bounds = m_text.getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    sf::Vector2f Span::onInflate(const sf::Vector2f &containerSize)
    {
        auto bounds = m_text.getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    void Span::onPlace(const sf::Vector2f &position)
    {
        auto bounds = m_text.getLocalBounds();
        m_place = {position.x - bounds.left, position.y - bounds.top};
    }

}