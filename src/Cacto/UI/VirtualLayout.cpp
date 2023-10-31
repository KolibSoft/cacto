#include <SFML/Window/Event.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/VirtualLayout.hpp>

namespace cacto
{

    VirtualLayout::VirtualLayout()
        : FrameLayout(),
          m_surface(Surface::Rectangle),
          m_texture()
    {
        m_surface.setColor(sf::Color::White);
    }

    VirtualLayout::~VirtualLayout() = default;

    VirtualLayout::VirtualLayout(const VirtualLayout &other)
        : FrameLayout(other),
          m_surface(other.m_surface),
          m_texture()
    {
    }

    VirtualLayout &VirtualLayout::operator=(const VirtualLayout &other)
    {
        FrameLayout::operator=(other);
        m_surface = other.m_surface;
        return *this;
    }

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        auto holder = dynamic_cast<const FrameHolder *>(getHolder());
        if (holder)
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
                DrawNode::draw(holder->child, m_texture, sf::RenderStates::Default);
                m_texture.display();
                target.draw(m_surface, states);
            }
        }
    }

    sf::Vector2f VirtualLayout::onCompact()
    {
        compactChildren();
        auto size = Block::compact({0, 0});
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
        Block::onPlace(position);
        auto contentBox = getContentBox();
        m_surface.place({contentBox.getLeft(), contentBox.getTop()});
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{0, 0};
            auto &boxSize = holder->size;
            switch (holder->hAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.x += contentSize.x - boxSize.x;
                break;
            case Center:
                contentPosition.x += (contentSize.x - boxSize.x) / 2;
                break;
            }
            switch (holder->vAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.y += contentSize.y - boxSize.y;
                break;
            case Center:
                contentPosition.y += (contentSize.y - boxSize.y) / 2;
                break;
            }
            InflatableNode::place(holder->child, contentPosition);
        }
    }

    bool VirtualLayout::onEvent(const sf::Event &event)
    {
        auto handled = false;
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            if (m_surface.contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
            {
                auto contentBox = getContentBox();
                auto _event = event;
                _event.mouseButton.x -= contentBox.getLeft();
                _event.mouseButton.y -= contentBox.getTop();
                handled = eventChildren(_event);
            }
            break;
        case sf::Event::MouseMoved:
            if (m_surface.contains({f32t(event.mouseMove.x), f32t(event.mouseMove.y)}))
            {
                auto contentBox = getContentBox();
                auto _event = event;
                _event.mouseMove.x -= contentBox.getLeft();
                _event.mouseMove.y -= contentBox.getTop();
                handled = eventChildren(_event);
            }
            break;
        case sf::Event::MouseWheelScrolled:
            if (m_surface.contains({f32t(event.mouseWheelScroll.x), f32t(event.mouseWheelScroll.y)}))
            {
                auto contentBox = getContentBox();
                auto _event = event;
                _event.mouseWheelScroll.x -= contentBox.getLeft();
                _event.mouseWheelScroll.y -= contentBox.getTop();
                handled = eventChildren(_event);
            }
            break;
        default:
            handled = eventChildren(event);
            break;
        }
        return handled;
    }

    bool VirtualLayout::onBubble(Node &target, const sf::Event &event)
    {
        auto handled = false;
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        {
            auto contentBox = getContentBox();
            auto _event = event;
            _event.mouseButton.x += contentBox.getLeft();
            _event.mouseButton.y += contentBox.getTop();
            handled = bubbleParent(target, _event);
        }
        break;
        case sf::Event::MouseMoved:
        {
            auto contentBox = getContentBox();
            auto _event = event;
            _event.mouseMove.x += contentBox.getLeft();
            _event.mouseMove.y += contentBox.getTop();
            handled = bubbleParent(target, _event);
        }
        break;
        case sf::Event::MouseWheelScrolled:
        {
            auto contentBox = getContentBox();
            auto _event = event;
            _event.mouseWheelScroll.x += contentBox.getLeft();
            _event.mouseWheelScroll.y += contentBox.getTop();
            handled = bubbleParent(target, _event);
        }
        break;
        default:
            handled = bubbleParent(target, event);
            break;
        }
        return handled;
    }

}