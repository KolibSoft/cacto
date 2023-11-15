#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Input.hpp>

namespace cacto
{

    const EventListener &Input::getOnInputListener() const
    {
        return m_onInput;
    }

    Input &Input::setOnInputListener(const EventListener &value)
    {
        m_onInput = value;
        return *this;
    }

    Input::Input(const sf::Font &font, const sf::String &string, u32t characterSize)
        : Label(font, string, characterSize),
          m_focused()
    {
    }

    Input::~Input() {}

    Input::Input(const Input &other)
        : Label(other),
          m_focused()
    {
    }

    Input &Input::operator=(const Input &other)
    {
        Label::operator=(other);
        return *this;
    }

    bool Input::onEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased && contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
        {
            focus();
            return true;
        }
        else if (m_focused && event.type == sf::Event::TextEntered)
        {
            onInput(event);
            return true;
        }
        return false;
    }

    void Input::onInput(const sf::Event &event)
    {
        auto string = getSpan().getString();
        auto character = static_cast<char32_t>(event.text.unicode);
        switch (character)
        {
        case 8:
            if (!string.isEmpty())
                string.erase(string.getSize() - 1, 1);
            break;
        default:
            string += character;
            break;
        }
        getSpan().setString(string);
        if (m_onInput)
            m_onInput(*this, event);
        else
            bubbleParent(*this, event);
    }

    void Input::onFocus(const sf::Event &event)
    {
        m_focused = true;
        bubbleParent(*this, event);
    }

    void Input::onUnfocus(const sf::Event &event)
    {
        m_focused = false;
        bubbleParent(*this, event);
    }

}