#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/Layout.hpp>

namespace cacto
{

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

    sf::Vector2f Layout::onCompact(const sf::Vector2f &contentSize)
    {
        auto _contentSize = contentSize;
        if (m_holders.size() > 0)
        {
            for (auto holder : m_holders)
            {
                auto size = InflatableNode::compact(holder->child, contentSize);
                _contentSize.x = std::max(size.x, _contentSize.x);
                _contentSize.y = std::max(size.y, _contentSize.y);
            }
        }
        auto boxSize = Block::onCompact(_contentSize);
        return boxSize;
    }

    sf::Vector2f Layout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        if (m_holders.size() > 0)
        {
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f _containerSize{box.getWidth(), box.getHeight()};
            for (auto holder : m_holders)
                InflatableNode::inflate(holder->child, _containerSize);
        }
        return boxSize;
    }

    void Layout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (m_holders.size() > 0)
        {
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f contentPosition{box.getLeft(), box.getTop()};
            for (auto holder : m_holders)
                InflatableNode::place(holder->child, contentPosition);
        }
    }

    Layout::Holder::Holder(Node &child)
        : child(child) {}

    Layout::Holder::~Holder() {}

}