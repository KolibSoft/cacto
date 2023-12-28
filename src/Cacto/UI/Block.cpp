#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    const std::string &Block::getId() const
    {
        return m_id;
    }

    Block &Block::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    Node *const Block::getBackground() const
    {
        return m_background;
    }

    Block &Block::setBackground(Node *const value)
    {
        Node *current = this;
        while (current)
        {
            if (current == value)
                throw std::runtime_error("The background is its own block ancestor");
            current = current->getParent();
        }
        m_background = value;
        return *this;
    }

    const Thickness &Block::getMargin() const
    {
        return m_margin;
    }

    Block &Block::setMargin(const Thickness &value)
    {
        m_margin = value;
        return *this;
    }

    const Thickness &Block::getPadding() const
    {
        return m_padding;
    }

    Block &Block::setPadding(const Thickness &value)
    {
        m_padding = value;
        return *this;
    }

    f32t Block::getMinWidth() const
    {
        return m_minWidth;
    }

    Block &Block::setMinWidth(f32t value)
    {
        m_minWidth = value;
        return *this;
    }

    f32t Block::getMaxWidth() const
    {
        return m_maxWidth;
    }

    Block &Block::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
        return *this;
    }

    f32t Block::getMinHeight() const
    {
        return m_minHeight;
    }

    Block &Block::setMinHeight(f32t value)
    {
        m_minHeight = value;
        return *this;
    }

    f32t Block::getMaxHeight() const
    {
        return m_maxHeight;
    }

    Block &Block::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
        return *this;
    }

    Block &Block::setFixedWidth(f32t value)
    {
        m_minWidth = value;
        m_maxWidth = value;
        return *this;
    }

    Block &Block::setFixedHeight(f32t value)
    {
        m_minHeight = value;
        m_maxHeight = value;
        return *this;
    }

    Box Block::getContainerBox() const
    {
        Box box{m_box};
        box.expand(m_margin);
        return box;
    }

    Box Block::getContentBox() const
    {
        Box box{m_box};
        box.shrink(m_padding);
        return box;
    }

    const Box &Block::asBox() const
    {
        return m_box;
    }

    Box &Block::asBox()
    {
        return m_box;
    }

    ParentNode *const Block::getParent() const
    {
        return m_parent;
    }

    void Block::drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background)
            DrawNode::draw(*m_background, target, states);
    }

    void Block::eventBlock(const sf::Event &event)
    {
        if (m_background)
            EventNode::event(*m_background, event);
    }

    sf::Vector2f Block::compactBlock(const sf::Vector2f &contentSize)
    {
        auto hMargin = m_margin.getHorizontal();
        auto vMargin = m_margin.getVertical();
        auto hPadding = m_padding.getHorizontal();
        auto vPadding = m_padding.getVertical();
        sf::Vector2f size{
            std::max(hPadding, std::max(m_minWidth, contentSize.x + hPadding)) + hMargin,
            std::max(vPadding, std::max(m_minHeight, contentSize.y + vPadding)) + vMargin};
        if (m_background)
            InflatableNode::compact(*m_background);
        m_box.setWidth(size.x);
        m_box.setHeight(size.y);
        return size;
    }

    sf::Vector2f Block::inflateBlock(const sf::Vector2f &containerSize)
    {
        auto hMargin = m_margin.getHorizontal();
        auto vMargin = m_margin.getVertical();
        sf::Vector2f size{std::max(m_box.getWidth(), std::min(containerSize.x, m_maxWidth + hMargin)),
                          std::max(m_box.getHeight(), std::min(containerSize.y, m_maxHeight + vMargin))};
        m_box.setWidth(size.x - hMargin);
        m_box.setHeight(size.y - vMargin);
        if (m_background)
            InflatableNode::inflate(*m_background, {m_box.getWidth(), m_box.getHeight()});
        return size;
    }

    void Block::attach(ParentNode &parent)
    {
        if (m_parent == &parent)
            return;
        if (m_parent != nullptr)
            throw std::runtime_error("This node is already attached to another parent");
        if (parent.hasAncestor(*this))
            throw std::runtime_error("This node is an ancestor");
        m_parent = &parent;
        parent.append(*this);
    }

    void Block::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    void Block::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
    }

    bool Block::event(const sf::Event &event)
    {
        eventBlock(event);
        auto handled = eventChildren(event);
        return handled;
    }

    sf::Vector2f Block::compact()
    {
        auto size = compactBlock({0, 0});
        return size;
    }

    sf::Vector2f Block::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        return size;
    }

    void Block::place(const sf::Vector2f &position)
    {
        placeBlock(position);
    }

    void Block::placeBlock(const sf::Vector2f &position)
    {
        m_box.setLeft(position.x + m_margin.left);
        m_box.setTop(position.y + m_margin.top);
        if (m_background)
            InflatableNode::place(*m_background, {m_box.getLeft(), m_box.getTop()});
    }

    Block::Block()
        : m_id(),
          m_box(),
          m_background(nullptr),
          m_margin(0),
          m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_parent()
    {
    }

    Block::~Block()
    {
        detach();
    }

}