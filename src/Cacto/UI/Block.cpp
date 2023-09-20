#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    Node *const Block::getParent() const
    {
        return m_parent;
    }

    void Block::attach(Node *const parent)
    {
        Node::attach(parent);
        m_parent = parent;
    }

    void Block::detach(Node *const parent)
    {
        Node::detach(parent);
        m_parent = nullptr;
    }

    const SharedNode &Block::getBackground() const
    {
        return m_background;
    }

    void Block::setBackground(const SharedNode &value)
    {
        m_background = value;
    }

    const Thickness &Block::getMargin() const
    {
        return m_margin;
    }

    void Block::setMargin(const Thickness &value)
    {
        m_margin = value;
    }

    const Thickness &Block::getPadding() const
    {
        return m_padding;
    }

    void Block::setPadding(const Thickness &value)
    {
        m_padding = value;
    }

    f32t Block::getMinWidth() const
    {
        return m_minWidth;
    }

    void Block::setMinWidth(f32t value)
    {
        m_minWidth = value;
    }

    f32t Block::getMaxWidth() const
    {
        return m_maxWidth;
    }

    void Block::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
    }

    f32t Block::getMinHeight() const
    {
        return m_minHeight;
    }

    void Block::setMinHeight(f32t value)
    {
        m_minHeight = value;
    }

    f32t Block::getMaxHeight() const
    {
        return m_maxHeight;
    }

    void Block::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
    }

    Block::Block()
        : m_parent(nullptr),
          m_background(nullptr),
          m_margin(0),
          m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity())
    {
    }

    Block::~Block() = default;

    bool Block::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background)
            DrawNode::draw(*m_background, target, states);
        return false;
    }

    sf::Vector2f Block::onCompact(const sf::Vector2f &contentSize)
    {
        sf::Vector2f _size{
            std::max(m_padding.getHorizontal(), std::max(m_minWidth, contentSize.x)) + m_margin.getHorizontal(),
            std::max(m_padding.getVertical(), std::max(m_minHeight, contentSize.y)) + m_margin.getVertical()};
        if (m_background)
            InflatableNode::compact(*m_background, _size);
        setWidth(_size.x);
        setHeight(_size.y);
        return _size;
    }

    sf::Vector2f Block::onInflate(const sf::Vector2f &containerSize)
    {
        sf::Vector2f _size{std::max(getWidth(), std::min(containerSize.x, m_maxWidth)),
                           std::max(getHeight(), std::min(containerSize.y, m_maxHeight))};
        setWidth(_size.x - m_margin.getHorizontal());
        setHeight(_size.y - m_margin.getVertical());
        if (m_background)
            InflatableNode::inflate(*m_background, {getWidth(), getHeight()});
        return _size;
    }

    void Block::onPlace(const sf::Vector2f &position)
    {
        setLeft(position.x + m_margin.left);
        setTop(position.y + m_margin.top);
        if (m_background)
            InflatableNode::place(*m_background, {getLeft(), getTop()});
    }

}