#include <SFML/Window/Event.hpp>
#include <Cacto/UI/ScrollLayout.hpp>

namespace cacto
{

    bool ScrollLayout::handle(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseMoved)
            m_hovered = containsVisualPoint({f32t(event.mouseMove.x), f32t(event.mouseMove.y)});
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
            m_shift = event.key.shift;
        if (VirtualLayout::handle(event))
            return true;
        if (event.type == sf::Event::MouseWheelScrolled && m_hovered && canScroll(event.mouseWheelScroll.delta * 5))
        {
            onScroll(event);
            return true;
        }
        return false;
    }

    void ScrollLayout::scroll(sf::Mouse::Wheel wheel, f32t delta, i32t x, i32t y)
    {
        sf::Event event{};
        event.type = sf::Event::MouseWheelScrolled;
        event.mouseWheelScroll.delta = delta;
        event.mouseWheelScroll.x = x;
        event.mouseWheelScroll.y = y;
        onScroll(event);
    }

    ScrollLayout::ScrollLayout()
        : VirtualLayout(),
          m_hovered(false),
          m_shift(false)
    {
    }

    ScrollLayout::~ScrollLayout() = default;

    bool ScrollLayout::canScroll(f32t delta) const
    {
        auto child = getChild();
        if (child)
        {
            auto contentBox = getContentBox();
            auto &childBox = getChildBox();
            sf::Vector2f childSize{childBox.getWidth(), childBox.getHeight()};
            if (!m_shift && contentBox.getHeight() < childSize.y)
            {
                sf::Vector2f childPlace{childBox.getLeft(), childBox.getTop()};
                childPlace.y += asTransformable().getPosition().y + delta;
                auto result = childPlace.y < 0 && childPlace.y + childSize.y > contentBox.getHeight();
                return result;
            }
            if (m_shift && contentBox.getWidth() < childSize.x)
            {
                sf::Vector2f childPlace{childBox.getLeft(), childBox.getTop()};
                childPlace.x += asTransformable().getPosition().x + delta;
                auto result = childPlace.x < 0 && childPlace.x + childSize.x > contentBox.getWidth();
                return result;
            }
        }
        return false;
    }

    void ScrollLayout::onScroll(const sf::Event &event)
    {
        if (m_shift)
            asTransformable().move({event.mouseWheelScroll.delta * 5, 0});
        else
            asTransformable().move({0, event.mouseWheelScroll.delta * 5});
    }

}