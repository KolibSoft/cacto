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
        : Label(font, string, characterSize)
    {
    }

    Button::~Button() {}

    Button::Button(const Button &other)
        : Label(other)
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
        return false;
    }

    void Button::onClick(const sf::Event &event)
    {
        if (m_onClick)
            m_onClick(*this, event);
        else
            bubbleParent(*this, event);
    }

}