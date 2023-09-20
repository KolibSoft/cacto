#include <stdexcept>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    szt FrameLayout::getChildCount() const
    {
        return m_holder && m_holder->child ? 1 : 0;
    }

    SharedNode FrameLayout::getChild(szt index) const
    {
        auto child = index == 0 && m_holder ? m_holder->child : nullptr;
        return child;
    }

    void FrameLayout::append(const SharedNode &child)
    {
        if (getChild())
            throw std::runtime_error("This node can not has more child nodes");
        Node::append(child);
        child->attach(this);
        m_holder.reset(new Holder());
        m_holder->child = child;
        m_holder->hAnchor = Start;
        m_holder->vAnchor = Start;
    }

    void FrameLayout::remove(const SharedNode &child)
    {
        if (getChild() != child)
            throw std::runtime_error("The node is not a child node");
        m_holder.reset();
        Node::remove(child);
        child->detach(this);
    }

    Box::Anchor FrameLayout::getHorizontalAnchor(const SharedNode &child) const
    {
        if (getChild() != child)
            throw std::runtime_error("The node is not a child");
        return m_holder->hAnchor;
    }

    void FrameLayout::setHorizontalAnchor(const SharedNode &child, Anchor value)
    {
        if (getChild() != child)
            throw std::runtime_error("The node is not a child");
        m_holder->hAnchor = value;
    }

    Box::Anchor FrameLayout::getVerticalAnchor(const SharedNode &child) const
    {
        if (getChild() != child)
            throw std::runtime_error("The node is not a child");
        return m_holder->vAnchor;
    }

    void FrameLayout::setVerticalAnchor(const SharedNode &child, Anchor value)
    {
        if (getChild() != child)
            throw std::runtime_error("The node is not a child");
        m_holder->vAnchor = value;
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr)
    {
    }

    FrameLayout::~FrameLayout() = default;

    bool FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        auto child = getChild();
        if (child)
            DrawNode::draw(*child, target, states);
        return false;
    }

    sf::Vector2f FrameLayout::onCompact(const sf::Vector2f &contentSize)
    {
        auto _contentSize = contentSize;
        auto child = getChild();
        if (child)
        {
            _contentSize = InflatableNode::compact(*child, contentSize);
            _contentSize.x = std::max(contentSize.x, _contentSize.x);
            _contentSize.y = std::max(contentSize.y, _contentSize.y);
        }
        auto boxSize = Block::onCompact(_contentSize);
        return boxSize;
    }

    sf::Vector2f FrameLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        auto child = getChild();
        if (child)
        {
            auto margin = getMargin();
            auto padding = getPadding();
            sf::Vector2f _containerSize{boxSize.x - margin.getHorizontal() - padding.getHorizontal(),
                                        boxSize.y - margin.getVertical() - padding.getVertical()};

            auto _boxSize = InflatableNode::inflate(*child, _containerSize);
            m_holder->boxSize = _boxSize;
        }
        return boxSize;
    }

    void FrameLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        auto child = getChild();
        if (child)
        {
            auto margin = getMargin();
            auto padding = getPadding();
            sf::Vector2f containerSize{
                getWidth() - padding.getHorizontal(),
                getHeight() - padding.getVertical(),
            };
            auto &boxSize = m_holder->boxSize;
            sf::Vector2f contentPosition{
                getLeft() + padding.left,
                getTop() + padding.top};
            switch (m_holder->hAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.x += containerSize.x - boxSize.x;
                break;
            case Center:
                contentPosition.x += (containerSize.x - boxSize.x) / 2;
                break;
            }
            switch (m_holder->vAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.y += containerSize.y - boxSize.y;
                break;
            case Center:
                contentPosition.y += (containerSize.y - boxSize.y) / 2;
                break;
            }
            InflatableNode::place(*child, contentPosition);
        }
    }

}