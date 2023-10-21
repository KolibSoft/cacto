#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Button.hpp>

namespace cacto
{

    const EventListener &Button::getOnClickListener() const
    {
        return m_onClick;
    }

    void Button::setOnClickListener(const EventListener &value)
    {
        m_onClick = value;
    }

    Button::Button(const sf::Font &font, const sf::String &string, u32t characterSize)
        : Label(font, string, characterSize),
          m_onClick(),
          m_focused()
    {
    }

    Button::~Button() {}

    Button::Button(const Button &other)
        : Label(other),
          m_focused()
    {
        m_onClick = other.m_onClick;
    }

    Button &Button::operator=(const Button &other)
    {
        Label::operator=(other);
        m_onClick = other.m_onClick;
        return *this;
    }

    bool Button::onEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased && getBlock().contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
        {
            onClick(event);
            return true;
        }
        else if (m_focused && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            click();
        }
        return false;
    }

    void Button::onClick(const sf::Event &event)
    {
        if (m_onClick)
            m_onClick(*this, event);
        else
            bubbleParent(*this, event);
        focus();
    }

    void Button::onFocus(const sf::Event &event)
    {
        m_focused = true;
        bubbleParent(*this, event);
    }

    void Button::onUnfocus(const sf::Event &event)
    {
        m_focused = false;
        bubbleParent(*this, event);
    }

}