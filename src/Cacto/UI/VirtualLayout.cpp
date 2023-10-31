#include <Cacto/UI/VirtualLayout.hpp>

namespace cacto
{

    VirtualLayout::VirtualLayout()
        : Block(),
          m_surface(Surface::Rectangle),
          m_texture()
    {
        m_surface.setColor(sf::Color::White);
    }

    VirtualLayout::~VirtualLayout() = default;

    VirtualLayout::VirtualLayout(const VirtualLayout &other)
        : Block(other),
          m_surface(other.m_surface),
          m_texture()
    {
    }

    VirtualLayout &VirtualLayout::operator=(const VirtualLayout &other)
    {
        Block::operator=(other);
        m_surface = other.m_surface;
        return *this;
    }

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        target.draw(m_surface, states);
    }

    sf::Vector2f VirtualLayout::onCompact(const sf::Vector2f &contentSize)
    {
        auto outerSize = Block::onCompact(contentSize);
        m_surface.compact();
        return outerSize;
    }

    sf::Vector2f VirtualLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto outerSize = Block::onInflate(containerSize);
        auto contentBox = getContentBox();
        m_surface.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return outerSize;
    }

    void VirtualLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        auto contentBox = getContentBox();
        m_surface.place({contentBox.getLeft(), contentBox.getTop()});
    }

}