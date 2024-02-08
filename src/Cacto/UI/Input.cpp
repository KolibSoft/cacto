#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Input.hpp>

namespace cacto
{

    Input &&Input::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Input &&Input::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Input &&Input::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Input &&Input::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Input &&Input::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Input &&Input::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Input &&Input::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Input &&Input::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    Input &&Input::setBackground(Node *const value)
    {
        Block::setBackground(value);
        return std::move(*this);
    }

    Input &&Input::setBackground(Node &&value)
    {
        Block::setBackground(std::move(value));
        return std::move(*this);
    }

    Input &&Input::setMargin(const Thickness &value)
    {
        Block::setMargin(value);
        return std::move(*this);
    }

    Input &&Input::setPadding(const Thickness &value)
    {
        Block::setPadding(value);
        return std::move(*this);
    }

    Input &&Input::setMinWidth(f32t value)
    {
        Block::setMinWidth(value);
        return std::move(*this);
    }

    Input &&Input::setMaxWidth(f32t value)
    {
        Block::setMaxWidth(value);
        return std::move(*this);
    }

    Input &&Input::setMinHeight(f32t value)
    {
        Block::setMinHeight(value);
        return std::move(*this);
    }

    Input &&Input::setMaxHeight(f32t value)
    {
        Block::setMaxHeight(value);
        return std::move(*this);
    }

    Input &&Input::setFixedWidth(f32t value)
    {
        Block::setFixedWidth(value);
        return std::move(*this);
    }

    Input &&Input::setFixedHeight(f32t value)
    {
        Block::setFixedHeight(value);
        return std::move(*this);
    }

    Input &&Input::setFont(const sf::Font *const value)
    {
        Label::setFont(value);
        return std::move(*this);
    }

    Input &&Input::setString(const sf::String &value)
    {
        Label::setString(value);
        return std::move(*this);
    }

    Input &&Input::setDirection(TextDirection value)
    {
        Label::setDirection(value);
        return std::move(*this);
    }

    Input &&Input::setCharacterSize(u32t value)
    {
        Label::setCharacterSize(value);
        return std::move(*this);
    }

    Input &&Input::setColor(const sf::Color &value)
    {
        Label::setColor(value);
        return std::move(*this);
    }

    Input &&Input::setHorizontalAnchor(BoxAnchor value)
    {
        Label::setHorizontalAnchor(value);
        return std::move(*this);
    }

    Input &&Input::setVerticalAnchor(BoxAnchor value)
    {
        Label::setVerticalAnchor(value);
        return std::move(*this);
    }

    const EventListener &Input::getOnInputListener() const
    {
        return m_onInput;
    }

    Input &Input::setOnInputListener(const EventListener &value)
    {
        m_onInput = value;
        return *this;
    }

    Input &&Input::setId(const std::string &value)
    {
        Block::setId(value);
        return std::move(*this);
    }

    Input *Input::clone() const
    {
        auto input = new Input(*this);
        return input;
    }

    Input *Input::acquire()
    {
        auto input = new Input(std::move(*this));
        return input;
    }

    bool Input::handle(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved && containsVisualPoint({f32t(event.mouseMove.x), f32t(event.mouseMove.y)}))
        {
            bubble(*this, event);
            return true;
        }
        else if (event.type == sf::Event::MouseButtonReleased && containsVisualPoint({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
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
        bubble(*this, event);
    }

    void Input::unfocus()
    {
        sf::Event event{};
        event.type = sf::Event::LostFocus;

        m_focused = false;
        bubble(*this, event);
    }

    Input::Input()
        : Label(),
          m_onInput(),
          m_focused()
    {
    }

    Input::~Input()
    {
        unfocus();
    }

    Input::Input(const Input &other)
        : Input()
    {
        *this = other;
    }

    Input &Input::operator=(const Input &other)
    {
        clone(other);
        return *this;
    }

    Input::Input(Input &&other)
        : Input()
    {
        *this = std::move(other);
    }

    Input &Input::operator=(Input &&other)
    {
        acquire(std::move(other));
        other.detach();
        return *this;
    }

    void Input::clone(const Input &other)
    {
        Label::clone(other);
        m_onInput = other.m_onInput;
    }

    void Input::acquire(Input &&other)
    {
        Label::acquire(std::move(other));
        m_onInput = other.m_onInput;
        other.m_onInput = nullptr;
        if (other.m_focused)
            focus();
    }

    void Input::onInput(const sf::Event &event)
    {
        auto string = getString();
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
        setString(string);
        if (m_onInput)
            m_onInput(*this, event);
        else
            bubble(*this, event);
    }

    XmlValue toXml(const Input &input)
    {
        XmlValue xml{"Input", {}};
        xml |= toXml((const Label &)input);
        return std::move(xml);
    }

    Input toInput(const XmlValue &xml)
    {
        Input button{};
        (Label &)button = toLabel(xml);
        return std::move(button);
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
                auto input = new Input();
                *input = toInput(xml);
                return input;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}