#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Button.hpp>

namespace cacto
{

    Button &&Button::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Button &&Button::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Button &&Button::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Button &&Button::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Button &&Button::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Button &&Button::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Button &&Button::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Button &&Button::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    Button &&Button::setBackground(Reference<Node> value)
    {
        Block::setBackground(std::move(value));
        return std::move(*this);
    }

    Button &&Button::setMargin(const Thickness &value)
    {
        Block::setMargin(value);
        return std::move(*this);
    }

    Button &&Button::setPadding(const Thickness &value)
    {
        Block::setPadding(value);
        return std::move(*this);
    }

    Button &&Button::setMinWidth(f32t value)
    {
        Block::setMinWidth(value);
        return std::move(*this);
    }

    Button &&Button::setMaxWidth(f32t value)
    {
        Block::setMaxWidth(value);
        return std::move(*this);
    }

    Button &&Button::setMinHeight(f32t value)
    {
        Block::setMinHeight(value);
        return std::move(*this);
    }

    Button &&Button::setMaxHeight(f32t value)
    {
        Block::setMaxHeight(value);
        return std::move(*this);
    }

    Button &&Button::setFixedWidth(f32t value)
    {
        Block::setFixedWidth(value);
        return std::move(*this);
    }

    Button &&Button::setFixedHeight(f32t value)
    {
        Block::setFixedHeight(value);
        return std::move(*this);
    }

    Button &&Button::setFont(const sf::Font *const value)
    {
        Label::setFont(value);
        return std::move(*this);
    }

    Button &&Button::setString(const sf::String &value)
    {
        Label::setString(value);
        return std::move(*this);
    }

    Button &&Button::setDirection(TextDirection value)
    {
        Label::setDirection(value);
        return std::move(*this);
    }

    Button &&Button::setCharacterSize(u32t value)
    {
        Label::setCharacterSize(value);
        return std::move(*this);
    }

    Button &&Button::setColor(const sf::Color &value)
    {
        Label::setColor(value);
        return std::move(*this);
    }

    Button &&Button::setHorizontalAnchor(BoxAnchor value)
    {
        Label::setHorizontalAnchor(value);
        return std::move(*this);
    }

    Button &&Button::setVerticalAnchor(BoxAnchor value)
    {
        Label::setVerticalAnchor(value);
        return std::move(*this);
    }

    const EventListener &Button::getOnClickListener() const
    {
        return m_onClick;
    }

    Button &&Button::setOnClickListener(const EventListener &value)
    {
        m_onClick = value;
        return std::move(*this);
    }

    Button &&Button::setId(const std::string &value)
    {
        Block::setId(value);
        return std::move(*this);
    }

    Button *Button::clone() const
    {
        auto button = new Button(*this);
        return button;
    }

    Button *Button::acquire()
    {
        auto button = new Button(std::move(*this));
        return button;
    }

    bool Button::handle(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved && containsVisualPoint({f32t(event.mouseMove.x), f32t(event.mouseMove.y)}))
        {
            bubble(*this, event);
            return true;
        }
        else if (event.type == sf::Event::MouseButtonReleased && containsVisualPoint({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
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
        event.mouseButton.x = position.x;
        event.mouseButton.y = position.y;
        onClick(event);
    }

    void Button::focus()
    {
        sf::Event event{};
        event.type = sf::Event::GainedFocus;

        m_focused = true;
        bubble(*this, event);
    }

    void Button::unfocus()
    {
        sf::Event event{};
        event.type = sf::Event::LostFocus;

        m_focused = false;
        bubble(*this, event);
    }

    Button::Button()
        : Label(),
          m_onClick(),
          m_focused()
    {
    }

    Button::~Button()
    {
        unfocus();
    }

    Button::Button(const Button &other)
        : Button()
    {
        *this = other;
    }

    Button &Button::operator=(const Button &other)
    {
        clone(other);
        return *this;
    }

    Button::Button(Button &&other)
        : Button()
    {
        *this = std::move(other);
    }

    Button &Button::operator=(Button &&other)
    {
        acquire(std::move(other));
        other.detach();
        return *this;
    }

    void Button::clone(const Button &other)
    {
        Label::clone(other);
        m_onClick = other.m_onClick;
    }

    void Button::acquire(Button &&other)
    {
        Label::acquire(std::move(other));
        m_onClick = other.m_onClick;
        other.m_onClick = nullptr;
        if (other.m_focused)
            focus();
    }

    void Button::onClick(const sf::Event &event)
    {
        if (m_onClick)
            m_onClick(*this, event);
        else
            bubble(*this, event);
        focus();
    }

    XmlValue toXml(const Button &button)
    {
        XmlValue xml{"Button", {}};
        xml |= toXml((const Label &)button);
        return std::move(xml);
    }

    Button toButton(const XmlValue &xml)
    {
        Button button{};
        (Label &)button = toLabel(xml);
        return std::move(button);
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
                auto button = new Button();
                *button = toButton(xml);
                return button;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}