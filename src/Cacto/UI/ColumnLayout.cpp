#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/ColumnLayout.hpp>

namespace cacto
{

    szt ColumnLayout::getChildCount() const
    {
        return m_holders.size();
    }

    Node *const ColumnLayout::getChild(szt index) const
    {
        if (index >= m_holders.size())
            return nullptr;
        auto &holder = m_holders.at(index);
        return &holder.getNode();
    }

    ColumnLayout::BoxAnchor ColumnLayout::getHorizontalAnchor(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getHorizontalAnchor();
    }

    ColumnLayout &ColumnLayout::setHorizontalAnchor(Node &child, BoxAnchor value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setHorizontalAnchor(value);
        return *this;
    }

    ColumnLayout::BoxAnchor ColumnLayout::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    ColumnLayout &ColumnLayout::setVerticalAnchor(BoxAnchor value)
    {
        m_vAnchor = value;
        return *this;
    }

    ColumnLayout::Direction ColumnLayout::getDirection() const
    {
        return m_direction;
    }

    ColumnLayout &ColumnLayout::setDirection(Direction value)
    {
        m_direction = value;
        return *this;
    }

    f32t ColumnLayout::getHorizontalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getHorizontalWeight();
    }

    ColumnLayout &ColumnLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setHorizontalWeight(value);
        return *this;
    }

    f32t ColumnLayout::getVerticalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getVerticalWeight();
    }

    ColumnLayout &ColumnLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setVerticalWeight(value);
        return *this;
    }

    ColumnLayout::Holder &ColumnLayout::append(Node &child)
    {
        Holder holder{child};
        m_holders.push_back(holder);
        return m_holders.back();
    }

    void ColumnLayout::remove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    ColumnLayout::ColumnLayout()
        : m_vAnchor(Start),
          m_direction(Forward),
          m_length(0),
          m_holders()
    {
    }

    ColumnLayout::~ColumnLayout()
    {
        while (m_holders.size() > 0)
            Node::unlink(*this, m_holders.back().getNode());
    }

    ColumnLayout::ColumnLayout(const ColumnLayout &other)
        : Block(other),
          m_vAnchor(other.m_vAnchor),
          m_direction(other.m_direction),
          m_length(0)
    {
    }

    ColumnLayout &ColumnLayout::operator=(const ColumnLayout &other)
    {
        Block::operator=(other);
        m_vAnchor = other.m_vAnchor;
        m_direction = other.m_direction;
        m_length = other.m_length;
        return *this;
    }

    void ColumnLayout::onAppend(Node &child)
    {
        Holder holder{child};
        m_holders.push_back(holder);
    }

    void ColumnLayout::onRemove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    void ColumnLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        drawChildren(target, states);
    }

    sf::Vector2f ColumnLayout::onCompact()
    {
        sf::Vector2f contentSize{0, 0};
        if (m_holders.size() > 0)
        {
            f32t length = 0;
            for (auto &holder : m_holders)
            {
                auto childSize = holder.compact();
                length += childSize.y;
                contentSize.x = std::max(childSize.x, contentSize.x);
            }
            m_length = length;
            contentSize.y = std::max(length, contentSize.y);
        }
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f ColumnLayout::onInflate(const sf::Vector2f &containerSize)
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
                length += childSize.y;
            }
            m_length = length;
        }
        return size;
    }

    void ColumnLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            f32t offset = 0;
            auto place = [&](Holder &holder)
            {
                auto _contentBox = contentBox;
                _contentBox.setTop(_contentBox.getTop() + offset);
                _contentBox.setWidth(holder.getBox().getWidth(), holder.getHorizontalAnchor());
                holder.place({_contentBox.getLeft(), _contentBox.getTop()});
                offset += holder.getBox().getHeight();
            };
            switch (m_direction)
            {
            case Forward:
                contentBox.setHeight(m_length, m_vAnchor);
                for (auto it = m_holders.begin(); it != m_holders.end(); ++it)
                    place(*it);
                break;
            case Reverse:
                switch (m_vAnchor)
                {
                case Start:
                    contentBox.setHeight(m_length, End);
                    break;
                case End:
                    contentBox.setHeight(m_length, Start);
                    break;
                case Center:
                    contentBox.setHeight(m_length, Center);
                    break;
                }
                for (auto it = m_holders.rbegin(); it != m_holders.rend(); ++it)
                    place(*it);
                break;
            }
        }
    }

    namespace column_layout
    {

        RowLayout::Anchor Holder::getHorizontalAnchor() const
        {
            return m_hAnchor;
        }

        Holder &Holder::setHorizontalAnchor(RowLayout::Anchor value)
        {
            m_hAnchor = value;
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
              m_hAnchor(RowLayout::Start),
              m_hWeight(1),
              m_vWeight(0)
        {
        }

        Holder::~Holder() = default;

    }

}