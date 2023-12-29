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

    bool Input::handle(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased && containsVisualPoint({float(event.mouseButton.x), float(event.mouseButton.y)}))
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

    void Input::input(u32t unicode)
    {
        sf::Event event{};
        event.type = sf::Event::TextEntered;
        event.text.unicode = unicode;
        onInput(event);
    }

    void Input::focus()
    {
        sf::Event event{};
        event.type = sf::Event::GainedFocus;

        m_focused = true;
        cacto::bubbleParent(*this, *this, event);
    }

    void Input::unfocus()
    {
        sf::Event event{};
        event.type = sf::Event::LostFocus;

        m_focused = false;
        cacto::bubbleParent(*this, *this, event);
    }

    Input::Input()
        : Label(),
          m_focused()
    {
    }

    Input::~Input() {}

    void Input::onInput(const sf::Event &event)
    {
        auto string = asSpan().getString();
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
        asSpan().setString(string);
        if (m_onInput)
            m_onInput(*this, event);
        else
            cacto::bubbleParent(*this, *this, event);
    }

    XmlValue CACTO_UI_API toXml(const Input &label)
    {
        auto xml = cacto::toXml((const Label &)label);
        xml.setName("Input");
        return std::move(xml);
    }

    void CACTO_UI_API fromXml(Input &input, const XmlValue &xml)
    {
        cacto::fromXml((Label &)input, xml);
    }

    namespace input
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Input *input = nullptr;
            if (value && typeid(*value) == typeid(Input) && (input = dynamic_cast<const Input *>(value)))
            {
                auto xml = cacto::toXml(*input);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Input")
            {
                auto input = std::make_shared<Input>();
                cacto::fromXml(*input, xml);
                Node::XmlStack.push(input);
                return input.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}