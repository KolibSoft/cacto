#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/VirtualLayout.hpp>

namespace cacto
{

    const sf::Transformable &VirtualLayout::getTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &VirtualLayout::getTransformable()
    {
        return m_transformable;
    }

    VirtualLayout::VirtualLayout()
        : FrameLayout(),
          m_transformable(),
          m_surface(Surface::Rectangle),
          m_texture()
    {
        m_surface.setColor(sf::Color::White);
    }

    VirtualLayout::~VirtualLayout() = default;

    VirtualLayout::VirtualLayout(const VirtualLayout &other)
        : FrameLayout(other),
          m_transformable(other.m_transformable),
          m_surface(other.m_surface),
          m_texture()
    {
    }

    VirtualLayout &VirtualLayout::operator=(const VirtualLayout &other)
    {
        FrameLayout::operator=(other);
        m_transformable = other.m_transformable;
        m_surface = other.m_surface;
        return *this;
    }

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        auto child = getChild();
        if (child)
        {
            auto contentBox = getContentBox();
            sf::Vector2u contentSize{u32t(contentBox.getWidth()), u32t(contentBox.getHeight())};
            if (contentSize.x > 0 && contentSize.y > 0)
            {
                if (contentSize != m_texture.getSize())
                {
                    auto _ = m_texture.create(contentSize);
                    m_surface.setTexture(&m_texture.getTexture());
                }
                m_texture.clear(sf::Color::Transparent);
                DrawNode::draw(*child, m_texture, m_transformable.getTransform());
                m_texture.display();
                target.draw(m_surface, states);
            }
        }
    }

    sf::Vector2f VirtualLayout::onCompact()
    {
        FrameLayout::onCompact();
        auto size = compactBlock({0, 0});
        m_surface.compact();
        return size;
    }

    sf::Vector2f VirtualLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = FrameLayout::onInflate(containerSize);
        auto contentBox = getContentBox();
        m_surface.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void VirtualLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        m_surface.place({contentBox.getLeft(), contentBox.getTop()});
        auto holder = getHolder();
        if (holder)
        {
            auto &childBox = holder->getBox();
            contentBox.setLeft(0);
            contentBox.setTop(0);
            contentBox.setWidth(childBox.getWidth(), getHorizontalAnchor());
            contentBox.setHeight(childBox.getHeight(), getVerticalAnchor());
            holder->place({contentBox.getLeft(), contentBox.getTop()});
        }
    }

    bool VirtualLayout::onEvent(const sf::Event &event)
    {
        auto child = getChild();
        if (child)
        {
            auto handled = false;
            auto map = [&](const sf::Vector2f &point)
            {
                auto contentBox = getContentBox();
                auto transform = m_transformable.getInverseTransform();
                sf::Vector2f mappedPoint{point.x, point.y};
                mappedPoint.x -= contentBox.getLeft();
                mappedPoint.y -= contentBox.getTop();
                mappedPoint = transform.transformPoint(mappedPoint);
                return mappedPoint;
            };
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            {
                sf::Vector2f point{f32t(event.mouseButton.x), f32t(event.mouseButton.y)};
                if (m_surface.contains(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseButton.x = point.x;
                    _event.mouseButton.y = point.y;
                    handled = EventNode::event(*child, _event);
                }
            }
            break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2f point{f32t(event.mouseMove.x), f32t(event.mouseMove.y)};
                if (m_surface.contains(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseMove.x = point.x;
                    _event.mouseMove.y = point.y;
                    handled = EventNode::event(*child, _event);
                }
            }
            break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Vector2f point{f32t(event.mouseWheelScroll.x), f32t(event.mouseWheelScroll.y)};
                if (m_surface.contains(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseWheelScroll.x = point.x;
                    _event.mouseWheelScroll.y = point.y;
                    handled = EventNode::event(*child, _event);
                }
            }
            break;
            default:
                handled = EventNode::event(*child, event);
                break;
            }
            return handled;
        }
        return false;
    }

    bool VirtualLayout::onBubble(Node &target, const sf::Event &event)
    {
        auto parent = getParent();
        if (parent)
        {
            auto handled = false;
            auto map = [&](const sf::Vector2f &point)
            {
                auto contentBox = getContentBox();
                auto transform = m_transformable.getTransform();
                sf::Vector2f mappedPoint{point.x, point.y};
                mappedPoint = transform.transformPoint(mappedPoint);
                mappedPoint.x += contentBox.getLeft();
                mappedPoint.y += contentBox.getTop();
                return mappedPoint;
            };
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            {
                sf::Vector2f point{f32t(event.mouseButton.x), f32t(event.mouseButton.y)};
                point = map(point);
                auto _event = event;
                _event.mouseButton.x = point.x;
                _event.mouseButton.y = point.y;
                handled = EventNode::bubble(*parent, target, _event);
            }
            break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2f point{f32t(event.mouseMove.x), f32t(event.mouseMove.y)};
                point = map(point);
                auto _event = event;
                _event.mouseMove.x = point.x;
                _event.mouseMove.y = point.y;
                handled = EventNode::bubble(*parent, target, _event);
            }
            break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Vector2f point{f32t(event.mouseWheelScroll.x), f32t(event.mouseWheelScroll.y)};
                point = map(point);
                auto _event = event;
                _event.mouseWheelScroll.x = point.x;
                _event.mouseWheelScroll.y = point.y;
                handled = EventNode::bubble(*parent, target, _event);
            }
            break;
            default:
                handled = EventNode::bubble(*parent, target, event);
                break;
            }
            return handled;
        }
        return false;
    }

}