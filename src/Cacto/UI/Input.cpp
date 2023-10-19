#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Input.hpp>

namespace cacto
{

    const EventListener &Input::getOnInputListener() const
    {
        return m_onInput;
    }

    void Input::setOnInputListener(const EventListener &value)
    {
        m_onInput = value;
    }

    Input::Input(const sf::Font &font, const sf::String &string, u32t characterSize)
        : Label(font, string, characterSize)
    {
    }

    Input::~Input() {}

    Input::Input(const Input &other)
        : Label(other)
    {
    }

    Input &Input::operator=(const Input &other)
    {
        Label::operator=(other);
        return *this;
    }

    bool Input::onEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::TextEntered)
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

}