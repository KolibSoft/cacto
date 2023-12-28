#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Button.hpp>

namespace cacto
{

    const EventListener &Button::getOnClickListener() const
    {
        return m_onClick;
    }

    Button &Button::setOnClickListener(const EventListener &value)
    {
        m_onClick = value;
        return *this;
    }

    bool Button::event(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased && contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
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

    void Button::click(sf::Mouse::Button button, const sf::Vector2f &position)
    {
        sf::Event event{};
        event.type = sf::Event::MouseButtonReleased;
        event.mouseButton.button = button;
        event.mouseButton.x = getLeft() + position.x;
        event.mouseButton.y = getTop() + position.y;
        onClick(event);
    }

    void Button::focus()
    {
        sf::Event event{};
        event.type = sf::Event::GainedFocus;

        m_focused = true;
        bubbleParent(*this, event);
    }

    void Button::unfocus()
    {
        sf::Event event{};
        event.type = sf::Event::LostFocus;

        m_focused = false;
        bubbleParent(*this, event);
    }

    Button::Button()
        : Label(),
          m_onClick(),
          m_focused()
    {
    }

    Button::~Button() {}

    void Button::onClick(const sf::Event &event)
    {
        if (m_onClick)
            m_onClick(*this, event);
        else
            bubbleParent(*this, event);
        focus();
    }

    XmlValue CACTO_UI_API toXml(const Button &label)
    {
        auto xml = cacto::toXml((const Label &)label);
        xml.setName("Button");
        return std::move(xml);
    }

    void CACTO_UI_API fromXml(Button &button, const XmlValue &xml)
    {
        cacto::fromXml((Label &)button, xml);
    }

    namespace button
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Button *button = nullptr;
            if (value && typeid(*value) == typeid(Button) && (button = dynamic_cast<const Button *>(value)))
            {
                auto xml = cacto::toXml(*button);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Button")
            {
                auto button = std::make_shared<Button>();
                cacto::fromXml(*button, xml);
                Node::XmlStack.push(button);
                return button.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}