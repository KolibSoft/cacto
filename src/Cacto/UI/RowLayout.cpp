#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/RowLayout.hpp>

namespace cacto
{

    szt RowLayout::getChildCount() const
    {
        return m_holders.size();
    }

    Node *const RowLayout::getChild(szt index) const
    {
        if (index >= m_holders.size())
            return nullptr;
        auto &holder = m_holders.at(index);
        return &holder.getNode();
    }

    RowLayout::Anchor RowLayout::getVerticalAnchor(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getVerticalAnchor();
    }

    RowLayout &RowLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setVerticalAnchor(value);
        return *this;
    }

    RowLayout::Anchor RowLayout::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    RowLayout &RowLayout::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
        return *this;
    }

    RowLayout::Direction RowLayout::getDirection() const
    {
        return m_direction;
    }

    RowLayout &RowLayout::setDirection(Direction value)
    {
        m_direction = value;
        return *this;
    }

    f32t RowLayout::getHorizontalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getHorizontalWeight();
    }

    RowLayout &RowLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setHorizontalWeight(value);
        return *this;
    }

    f32t RowLayout::getVerticalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getVerticalWeight();
    }

    RowLayout &RowLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setVerticalWeight(value);
        return *this;
    }

    RowLayout::Holder &RowLayout::append(Node &child)
    {
        Holder holder{child};
        m_holders.push_back(holder);
        return m_holders.back();
    }

    void RowLayout::remove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    RowLayout::RowLayout()
        : m_hAnchor(Start),
          m_direction(Forward),
          m_length(0),
          m_holders()
    {
    }

    RowLayout::~RowLayout()
    {
        while (m_holders.size() > 0)
            Node::unlink(*this, m_holders.back().getNode());
    }

    RowLayout::RowLayout(const RowLayout &other)
        : Block(other),
          m_hAnchor(other.m_hAnchor),
          m_direction(other.m_direction),
          m_length(0),
          m_holders()
    {
    }

    RowLayout &RowLayout::operator=(const RowLayout &other)
    {
        Block::operator=(other);
        m_hAnchor = other.m_hAnchor;
        m_direction = other.m_direction;
        m_length = other.m_length;
        return *this;
    }

    void RowLayout::onAppend(Node &child)
    {
        Holder holder{child};
        m_holders.push_back(holder);
    }

    void RowLayout::onRemove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    void RowLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        drawChildren(target, states);
    }

    sf::Vector2f RowLayout::onCompact()
    {
        sf::Vector2f contentSize{0, 0};
        if (getChildCount() > 0)
        {
            f32t length = 0;
            for (auto &holder : m_holders)
            {
                auto childSize = holder.compact();
                length += childSize.x;
                contentSize.y = std::max(childSize.y, contentSize.y);
            }
            m_length = length;
            contentSize.x = std::max(length, contentSize.x);
        }
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f RowLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_holders.size() > 0)
        {
            f32t length = 0;
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            for (auto &holder : m_holders)
            {
                auto childSize = holder.inflate({contentSize.x * holder.getHorizontalWeight(), contentSize.y * holder.getVerticalWeight()});
                length += childSize.x;
            }
            m_length = length;
        }
        return size;
    }

    void RowLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            f32t offset = 0;
            auto place = [&](Holder &holder)
            {
                auto _contentBox = contentBox;
                _contentBox.setLeft(_contentBox.getLeft() + offset);
                _contentBox.setHeight(holder.getBox().getHeight(), holder.getVerticalAnchor());
                holder.place({_contentBox.getLeft(), _contentBox.getTop()});
                offset += holder.getBox().getWidth();
            };
            switch (m_direction)
            {
            case Forward:
                contentBox.setWidth(m_length, m_hAnchor);
                for (auto it = m_holders.begin(); it != m_holders.end(); ++it)
                    place(*it);
                break;
            case Reverse:
                switch (m_hAnchor)
                {
                case Start:
                    contentBox.setWidth(m_length, End);
                    break;
                case End:
                    contentBox.setWidth(m_length, Start);
                    break;
                case Center:
                    contentBox.setWidth(m_length, Center);
                    break;
                }
                for (auto it = m_holders.rbegin(); it != m_holders.rend(); ++it)
                    place(*it);
                break;
            }
        }
    }

    namespace row_layout
    {

        RowLayout::Anchor Holder::getVerticalAnchor() const
        {
            return m_vAnchor;
        }

        Holder &Holder::setVerticalAnchor(RowLayout::Anchor value)
        {
            m_vAnchor = value;
            return *this;
        }

        f32t Holder::getHorizontalWeight() const
        {
            return m_hWeight;
        }

        Holder &Holder::setHorizontalWeight(f32t value)
        {
            m_hWeight = value;
            return *this;
        }

        f32t Holder::getVerticalWeight() const
        {
            return m_vWeight;
        }

        Holder &Holder::setVerticalWeight(f32t value)
        {
            m_vWeight = value;
            return *this;
        }

        Holder::Holder(Node &node)
            : layout::Holder(node),
              m_vAnchor(RowLayout::Start),
              m_hWeight(0),
              m_vWeight(1)
        {
        }

        Holder::~Holder() = default;

    }

}