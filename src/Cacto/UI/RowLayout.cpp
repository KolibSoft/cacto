#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/RowLayout.hpp>

namespace cacto
{

    void RowLayout::append(Node &child)
    {
        Node::link(*this, child);
    }

    void RowLayout::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    RowLayout::RowLayout() {}

    RowLayout::~RowLayout() {}

    RowLayout::RowLayout(const RowLayout &other)
        : Block(other)
    {
    }

    RowLayout &RowLayout::operator=(const RowLayout &other)
    {
        Block::operator=(other);
        return *this;
    }

    const RowLayout::Holder *const RowLayout::getHolder(const Node &node) const
    {
        for (auto &holder : m_holders)
        {
            if (holder.child == &node)
                return &holder;
        }
        return nullptr;
    }

    RowLayout::Holder *const RowLayout::getHolder(const Node &node)
    {
        for (auto &holder : m_holders)
        {
            if (holder.child == &node)
                return &holder;
        }
        return nullptr;
    }

    void RowLayout::onAppend(Node &child)
    {
        auto holder = getHolder(child);
        if (holder != nullptr)
            throw std::runtime_error("This node can not has more child nodes");
        Holder _holder{};
        _holder.child = &child;
        m_holders.push_back(_holder);
    }

    void RowLayout::onRemove(Node &child)
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child node");
        m_holders.erase(std::find_if(m_holders.begin(), m_holders.end(), [holder](auto &it)
                                     { return &it == holder; }));
    }

}