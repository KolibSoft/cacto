#include <stdexcept>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    szt FrameLayout::getChildCount() const
    {
        return m_child != nullptr ? 1 : 0;
    }

    Node *const FrameLayout::getChild(szt index) const
    {
        return index == 0 ? m_child : nullptr;
    }

    FrameLayout::Anchor FrameLayout::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void FrameLayout::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    FrameLayout::Anchor FrameLayout::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void FrameLayout::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    void FrameLayout::append(Node &child)
    {
        Node::link(*this, child);
    }

    void FrameLayout::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    FrameLayout::FrameLayout()
        : Block(),
          m_child(nullptr),
          m_hAnchor(Start),
          m_vAnchor(Start),
          m_childSize()
    {
    }

    FrameLayout::~FrameLayout()
    {
        if (m_child)
            Node::unlink(*this, *m_child);
    }

    FrameLayout::FrameLayout(const FrameLayout &other)
        : Block(other),
          m_child(nullptr),
          m_hAnchor(other.m_hAnchor),
          m_vAnchor(other.m_vAnchor),
          m_childSize()
    {
    }

    FrameLayout &FrameLayout::operator=(const FrameLayout &other)
    {
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        return *this;
    }

    void FrameLayout::onAppend(Node &child)
    {
        if (m_child != nullptr)
            throw std::runtime_error("This node has another child already");
        m_child = &child;
    }

    void FrameLayout::onRemove(Node &child)
    {
        if (m_child != &child)
            throw std::runtime_error("This node has another child already");
        m_child = nullptr;
    }

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(dynamic_cast<const DrawNode &>(*m_child), states);
    }

    sf::Vector2f FrameLayout::onCompact()
    {
        auto contentSize = m_child ? InflatableNode::compact(*m_child) : sf::Vector2f{0, 0};
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f FrameLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_child)
        {
            auto contentBox = getContentBox();
            m_childSize = InflatableNode::inflate(*m_child, {contentBox.getWidth(), contentBox.getHeight()});
        }
        return size;
    }

    void FrameLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (m_child)
        {
            auto contentBox = getContentBox();
            contentBox.setWidth(m_childSize.x, m_hAnchor);
            contentBox.setHeight(m_childSize.y, m_vAnchor);
            InflatableNode::place(*m_child, {contentBox.getLeft(), contentBox.getTop()});
        }
    }

}