#include <SFML/Window/Event.hpp>
#include <Cacto/UI/ScrollLayout.hpp>

namespace cacto
{

    ScrollLayout::ScrollLayout()
        : VirtualLayout(),
          m_hovered(false),
          m_shift(false)
    {
    }

    ScrollLayout::~ScrollLayout() = default;

    ScrollLayout::ScrollLayout(const ScrollLayout &other)
        : VirtualLayout(other),
          m_hovered(false),
          m_shift(false)
    {
    }

    ScrollLayout &ScrollLayout::operator=(const ScrollLayout &other)
    {
        VirtualLayout::operator=(other);
        return *this;
    }

    bool ScrollLayout::canScroll(f32t delta) const
    {
        auto contentBox = getContentBox();
        auto childSize = getChildSize();
        if (!m_shift && contentBox.getHeight() < childSize.y)
        {
            auto childPlace = getChildPlace();
            childPlace.y += getTransformable().getPosition().y + delta;
            auto result = childPlace.y < 0 && childPlace.y + childSize.y > contentBox.getHeight();
            return result;
        }
        if (m_shift && contentBox.getWidth() < childSize.x)
        {
            auto childPlace = getChildPlace();
            childPlace.x += getTransformable().getPosition().x + delta;
            auto result = childPlace.x < 0 && childPlace.x + childSize.x > contentBox.getWidth();
            return result;
        }
        return false;
    }

    bool ScrollLayout::onEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved)
            m_hovered = contains({f32t(event.mouseMove.x), f32t(event.mouseMove.y)});
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
            m_shift = event.key.shift;
        if (VirtualLayout::onEvent(event))
            return true;
        if (event.type == sf::Event::MouseWheelScrolled && m_hovered && canScroll(event.mouseWheelScroll.delta * 5))
        {
            onScroll(event);
            return true;
        }
        return false;
    }

    void ScrollLayout::onScroll(const sf::Event &event)
    {
        if (m_shift)
            getTransformable().move({event.mouseWheelScroll.delta * 5, 0});
        else
            getTransformable().move({0, event.mouseWheelScroll.delta * 5});
    }

}