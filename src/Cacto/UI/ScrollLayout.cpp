#include <Cacto/UI/ScrollLayout.hpp>

namespace cacto
{

    ScrollLayout::ScrollLayout()
        : VirtualLayout(),
          m_scroll(),
          m_hovered(false),
          m_shift(false)
    {
    }

    ScrollLayout::~ScrollLayout() = default;

    ScrollLayout::ScrollLayout(const ScrollLayout &other)
        : VirtualLayout(other),
          m_scroll(other.m_scroll),
          m_hovered(false),
          m_shift(false)
    {
    }

    ScrollLayout &ScrollLayout::operator=(const ScrollLayout &other)
    {
        VirtualLayout::operator=(other);
        m_scroll = other.m_scroll;
        return *this;
    }

    bool ScrollLayout::onEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved)
            m_hovered = contains({f32t(event.mouseMove.x), f32t(event.mouseMove.y)});
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
            m_shift = event.key.shift;
        if (VirtualLayout::onEvent(event))
            return true;
        if (event.type == sf::Event::MouseWheelScrolled && m_hovered)
        {
            onScroll(event);
            return true;
        }
        return false;
    }

    void ScrollLayout::onScroll(const sf::Event &event)
    {
        auto childSize = getChildSize();
        auto contentBox = getContentBox();
        if (!m_shift && contentBox.getHeight() < childSize.y)
        {
            auto childPlace = getChildPlace();
            auto delta = event.mouseWheelScroll.delta;
            childPlace.y += m_scroll.y + delta;
            if (childPlace.y < 0 && childPlace.y + childSize.y > contentBox.getHeight())
            {
                m_scroll.y += delta;
                getTransformable().setPosition(m_scroll);
            }
        }
        if (m_shift && contentBox.getWidth() < childSize.x)
        {
            auto childPlace = getChildPlace();
            auto delta = event.mouseWheelScroll.delta;
            childPlace.x += m_scroll.x + delta;
            if (childPlace.x < 0 && childPlace.x + childSize.x > contentBox.getWidth())
            {
                m_scroll.x += delta;
                getTransformable().setPosition(m_scroll);
            }
        }
    }

}