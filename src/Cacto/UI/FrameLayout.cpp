#include <stdexcept>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    FrameLayout::Anchor FrameLayout::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    FrameLayout &FrameLayout::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
        return *this;
    }

    FrameLayout::Anchor FrameLayout::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    FrameLayout &FrameLayout::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
        return *this;
    }

    ParentNode *const FrameLayout::getParent() const
    {
        return Block::getParent();
    }

    szt FrameLayout::getChildCount() const
    {
        return m_child != nullptr ? 1 : 0;
    }

    ChildNode *const FrameLayout::getChild(szt index) const
    {
        if (index >= 1)
            return nullptr;
        return m_child;
    }

    void FrameLayout::append(ChildNode &child)
    {
        if (m_child == &child)
            return;
        if (m_child != nullptr)
            throw std::runtime_error("This node has another child already");
        if (child.getParent() != nullptr && child.getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
        if (hasAncestor(child))
            throw std::runtime_error("The node is an ancestor");
        m_child = &child;
        child.attach(*this);
    }

    void FrameLayout::remove(ChildNode &child)
    {
        if (m_child == &child)
        {
            m_child = nullptr;
            child.detach();
        }
    }

    void FrameLayout::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        if (m_child)
            DrawNode::draw(*m_child, target, states);
    }

    sf::Vector2f FrameLayout::compact()
    {
        auto contentSize = m_child ? InflatableNode::compact(*m_child) : sf::Vector2f{0, 0};
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f FrameLayout::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_child)
        {
            auto contentBox = getContentBox();
            m_childSize = InflatableNode::inflate(*m_child, {contentBox.getWidth(), contentBox.getHeight()});
        }
        return size;
    }

    void FrameLayout::place(const sf::Vector2f &position)
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

    FrameLayout::FrameLayout()
        : Block(),
          m_hAnchor(Start),
          m_vAnchor(Start),
          m_childSize(),
          m_child()
    {
    }

    FrameLayout::~FrameLayout()
    {
        if (m_child)
            remove(*m_child);
    }

}