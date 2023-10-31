#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    szt Layout::getChildCount() const
    {
        auto count = m_holders.size();
        return count;
    }

    Node *const Layout::getChild(szt index) const
    {
        auto holder = getHolder(index);
        if (holder)
            return &holder->child;
        return nullptr;
    }

    void Layout::append(Node &child)
    {
        Node::link(*this, child);
    }

    void Layout::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    Layout::Layout()
        : m_holders()
    {
    }

    Layout::~Layout()
    {
        while (m_holders.size() > 0)
        {
            auto holder = m_holders.front();
            Node::unlink(*this, holder->child);
        }
    }

    Layout::Layout(const Layout &other)
        : Block(other),
          m_holders()
    {
    }

    Layout &Layout::operator=(const Layout &other)
    {
        Block::operator=(other);
        return *this;
    }

    Layout::Holder *const Layout::getHolder(szt index)
    {
        if (index < m_holders.size())
        {
            auto holder = m_holders[index];
            return holder;
        }
        return nullptr;
    }

    const Layout::Holder *const Layout::getHolder(szt index) const
    {
        if (index < m_holders.size())
        {
            auto holder = m_holders[index];
            return holder;
        }
        return nullptr;
    }

    Layout::Holder *const Layout::getHolder(const Node &child)
    {
        for (auto holder : m_holders)
        {
            if (&holder->child == &child)
                return holder;
        }
        return nullptr;
    }

    const Layout::Holder *const Layout::getHolder(const Node &child) const
    {
        for (auto holder : m_holders)
        {
            if (&holder->child == &child)
                return holder;
        }
        return nullptr;
    }

    Layout::Holder *Layout::onHold(Node &child) const
    {
        auto holder = new Holder(child);
        return holder;
    }

    void Layout::onAppend(Node &child)
    {
        auto holder = getHolder(child);
        if (holder != nullptr)
            throw std::runtime_error("This node is a child already");
        holder = onHold(child);
        m_holders.push_back(holder);
    }

    void Layout::onRemove(Node &child)
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        m_holders.erase(std::find(m_holders.begin(), m_holders.end(), holder));
        delete holder;
    }

    void Layout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        for (auto holder : m_holders)
            DrawNode::draw(holder->child, target, states);
    }

    sf::Vector2f Layout::onCompact()
    {
        auto contentSize = compactChildren();
        auto size = Block::compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Layout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = Block::onInflate(containerSize);
        if (m_holders.size() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            inflateChildren(contentSize);
        }
        return size;
    }

    void Layout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (m_holders.size() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            placeChildren(contentPosition);
        }
    }

    Layout::Holder::Holder(Node &child)
        : child(child)
    {
    }

    Layout::Holder::~Holder() = default;

}