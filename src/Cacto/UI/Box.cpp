#define COLIB_UI_EXPORTS
#include <SFML/System/Vector2.hpp>
#include <Cacto/UI/Thickness.hpp>
#include <Cacto/UI/Box.hpp>

namespace cacto
{

    f32t Box::getLeft() const
    {
        return m_rect.left;
    }

    void Box::setLeft(f32t value, bool resize)
    {
        if (resize)
        {
            m_rect.width += m_rect.left - value;
        }
        m_rect.left = value;
    }

    f32t Box::getRight() const
    {
        return m_rect.left + m_rect.width;
    }

    void Box::setRight(f32t value, bool resize)
    {
        if (resize)
        {
            m_rect.width = value - m_rect.left;
        }
        m_rect.left = value - m_rect.width;
    }

    f32t Box::getTop() const
    {
        return m_rect.top;
    }

    void Box::setTop(f32t value, bool resize)
    {
        if (resize)
        {
            m_rect.height += m_rect.top - value;
        }
        m_rect.top = value;
    }

    f32t Box::getBottom() const
    {
        return m_rect.top + m_rect.height;
    }

    void Box::setBottom(f32t value, bool resize)
    {
        if (resize)
        {
            m_rect.height = value - m_rect.top;
        }
        m_rect.top = value - m_rect.height;
    }

    f32t Box::getWidth() const
    {
        return m_rect.width;
    }

    void Box::setWidth(f32t value, Anchor anchor)
    {
        switch (anchor)
        {
        case Start:
            break;
        case End:
            m_rect.left -= value - m_rect.width;
            break;
        case Center:
            m_rect.left -= (value - m_rect.width) / 2;
            break;
        }
        m_rect.width = value;
    }

    f32t Box::getHeight() const
    {
        return m_rect.height;
    }

    void Box::setHeight(f32t value, Anchor anchor)
    {
        switch (anchor)
        {
        case Start:
            break;
        case End:
            m_rect.top -= value - m_rect.height;
            break;
        case Center:
            m_rect.top -= (value - m_rect.height) / 2;
            break;
        }
        m_rect.height = value;
    }

    void Box::shrink(const Thickness &thickness)
    {
        m_rect.left += thickness.left;
        m_rect.top += thickness.top;
        m_rect.width -= thickness.getHorizontal();
        m_rect.height -= thickness.getVertical();
    }

    void Box::expand(const Thickness &thickness)
    {
        m_rect.left -= thickness.left;
        m_rect.top -= thickness.top;
        m_rect.width += thickness.getHorizontal();
        m_rect.height += thickness.getVertical();
    }

    bool Box::contains(const sf::Vector2f &point) const
    {
        auto result = m_rect.contains(point);
        return result;
    }

    Box::Box(const sf::FloatRect &rect)
        : m_rect(rect)
    {
    }

    Box::operator const sf::FloatRect &() const
    {
        return m_rect;
    }

    Box::~Box()
    {
    }

    std::string toString(Box::Anchor anchor)
    {
        if (anchor == Box::Start)
            return "Start";
        else if (anchor == Box::End)
            return "End";
        else if (anchor == Box::Center)
            return "Center";
        else
            throw std::runtime_error("Invalid anchor value");
    }

    void fromString(Box::Anchor &anchor, const std::string &string)
    {
        if (string == "Start")
            anchor = Box::Start;
        else if (string == "End")
            anchor = Box::End;
        else if (string == "Center")
            anchor = Box::Center;
        else
            throw std::runtime_error("Invalid anchor value");
    }

}