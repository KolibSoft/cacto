#include <stdexcept>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    szt FrameLayout::getChildCount() const
    {
        return m_holder != nullptr ? 1 : 0;
    }

    Node *const FrameLayout::getChild(szt index) const
    {
        if (index >= 1 || !m_holder)
            return nullptr;
        return &m_holder->getNode();
    }

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
          m_hAnchor(Start),
          m_vAnchor(Start),
          m_holder()
    {
    }

    FrameLayout::~FrameLayout()
    {
        if (m_holder)
            Node::unlink(*this, m_holder->getNode());
    }

    FrameLayout::FrameLayout(const FrameLayout &other)
        : Block(other),
          m_hAnchor(other.m_hAnchor),
          m_vAnchor(other.m_vAnchor),
          m_holder(nullptr)
    {
    }

    FrameLayout &FrameLayout::operator=(const FrameLayout &other)
    {
        Block::operator=(other);
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        return *this;
    }

    const FrameLayout::Holder *const FrameLayout::getHolder() const
    {
        return m_holder;
    }

    FrameLayout::Holder *const FrameLayout::getHolder()
    {
        return m_holder;
    }

    void FrameLayout::onAppend(Node &child)
    {
        if (m_holder != nullptr)
            throw std::runtime_error("This node has another child already");
        m_holder = new Holder(child);
    }

    void FrameLayout::onRemove(Node &child)
    {
        if (!m_holder || &m_holder->getNode() != &child)
            throw std::runtime_error("This node has another child already");
        delete m_holder;
        m_holder = nullptr;
    }

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        if (m_holder)
            DrawNode::draw(m_holder->getNode(), target, states);
    }

    sf::Vector2f FrameLayout::onCompact()
    {
        auto contentSize = m_holder ? m_holder->compact() : sf::Vector2f{0, 0};
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f FrameLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_holder)
        {
            auto contentBox = getContentBox();
            m_holder->inflate({contentBox.getWidth(), contentBox.getHeight()});
        }
        return size;
    }

    void FrameLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (m_holder)
        {
            auto contentBox = getContentBox();
            auto &childBox = m_holder->getBox();
            contentBox.setWidth(childBox.getWidth(), m_hAnchor);
            contentBox.setHeight(childBox.getHeight(), m_vAnchor);
            m_holder->place({contentBox.getLeft(), contentBox.getTop()});
        }
    }

}