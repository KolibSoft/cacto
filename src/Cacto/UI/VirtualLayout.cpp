#include <SFML/Window/Event.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/NodeUtils.hpp>
#include <Cacto/UI/VirtualLayout.hpp>

namespace cacto
{

    const sf::Transformable &VirtualLayout::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &VirtualLayout::asTransformable()
    {
        return m_transformable;
    }

    sf::Vector2f VirtualLayout::compact()
    {
        FrameLayout::compact();
        auto size = compactBlock({0, 0});
        m_surface.compact();
        return size;
    }

    sf::Vector2f VirtualLayout::inflate(const sf::Vector2f &containerSize)
    {
        auto size = FrameLayout::inflate(containerSize);
        auto contentBox = getContentBox();
        m_surface.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void VirtualLayout::place(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        m_surface.place({contentBox.getLeft(), contentBox.getTop()});
        auto child = getChild();
        if (child)
        {
            auto &childBox = getChildBox();
            contentBox.setLeft(0);
            contentBox.setTop(0);
            contentBox.setWidth(childBox.getWidth(), getHorizontalAnchor());
            contentBox.setHeight(childBox.getHeight(), getVerticalAnchor());
            cacto::place(*child, {contentBox.getLeft(), contentBox.getTop()});
        }
    }

    bool VirtualLayout::handle(const sf::Event &event)
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
                if (m_surface.containsVisualPoint(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseButton.x = point.x;
                    _event.mouseButton.y = point.y;
                    handled = cacto::handle(*child, _event);
                }
            }
            break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2f point{f32t(event.mouseMove.x), f32t(event.mouseMove.y)};
                if (m_surface.containsVisualPoint(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseMove.x = point.x;
                    _event.mouseMove.y = point.y;
                    handled = cacto::handle(*child, _event);
                }
            }
            break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Vector2f point{f32t(event.mouseWheelScroll.x), f32t(event.mouseWheelScroll.y)};
                if (m_surface.containsVisualPoint(point))
                {
                    point = map(point);
                    auto _event = event;
                    _event.mouseWheelScroll.x = point.x;
                    _event.mouseWheelScroll.y = point.y;
                    handled = cacto::handle(*child, _event);
                }
            }
            break;
            default:
                handled = cacto::handle(*child, event);
                break;
            }
            return handled;
        }
        return false;
    }

    bool VirtualLayout::bubble(Node &target, const sf::Event &event)
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
                handled = cacto::bubble(*parent, target, _event);
            }
            break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2f point{f32t(event.mouseMove.x), f32t(event.mouseMove.y)};
                point = map(point);
                auto _event = event;
                _event.mouseMove.x = point.x;
                _event.mouseMove.y = point.y;
                handled = cacto::bubble(*parent, target, _event);
            }
            break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Vector2f point{f32t(event.mouseWheelScroll.x), f32t(event.mouseWheelScroll.y)};
                point = map(point);
                auto _event = event;
                _event.mouseWheelScroll.x = point.x;
                _event.mouseWheelScroll.y = point.y;
                handled = cacto::bubble(*parent, target, _event);
            }
            break;
            default:
                handled = cacto::bubble(*parent, target, event);
                break;
            }
            return handled;
        }
        return false;
    }

    VirtualLayout::VirtualLayout()
        : FrameLayout(),
          m_transformable(),
          m_surface(),
          m_texture()
    {
        m_surface
            .setGeometry(&Rectangle::Identity)
            .setColor(sf::Color::White);
    }

    VirtualLayout::~VirtualLayout() = default;

    void VirtualLayout::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
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
                cacto::draw(*child, m_texture, m_transformable.getTransform());
                m_texture.display();
                target.draw(m_surface, states);
            }
        }
    }

}