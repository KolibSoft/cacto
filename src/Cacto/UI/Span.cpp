#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/FontPack.hpp>
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
        return &m_text.getFont();
    }

    Span &Span::setFont(const sf::Font *const value)
    {
        m_text.setFont(*value);
        return *this;
    }

    const sf::String &Span::getString() const
    {
        return m_text.getString();
    }

    Span &Span::setString(const sf::String &value)
    {
        m_text.setString(value);
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
        if (getFont())
        {
            auto _states = states;
            _states.transform.translate(m_place);
            target.draw(m_text, _states);
        }
    }

    sf::Vector2f Span::compact()
    {
        auto bounds = m_text.getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    sf::Vector2f Span::inflate(const sf::Vector2f &containerSize)
    {
        auto bounds = m_text.getLocalBounds();
        sf::Vector2f size{bounds.width, bounds.height};
        return size;
    }

    void Span::place(const sf::Vector2f &position)
    {
        auto bounds = m_text.getLocalBounds();
        m_place = {position.x - bounds.left, position.y - bounds.top};
    }

    Span::Span()
        : m_id(),
          m_text(*cacto::getFont("Default")),
          m_place(),
          m_parent()
    {
    }

    Span::~Span() = default;

}