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
        Box box{*this};
        box.expand(m_margin);
        return box;
    }

    Box Block::getContentBox() const
    {
        Box box{*this};
        box.shrink(m_padding);
        return box;
    }

    Block::Block()
        : m_parent(),
          m_background(nullptr),
          m_margin(0),
          m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity())
    {
    }

    Block::~Block()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

    Block::Block(const Block &other)
        : Box(other),
          m_parent(),
          m_background(nullptr),
          m_margin(other.m_margin),
          m_padding(other.m_padding),
          m_minWidth(other.m_minWidth), m_maxWidth(other.m_maxWidth),
          m_minHeight(other.m_minHeight), m_maxHeight(other.m_maxHeight)
    {
    }

    Block &Block::operator=(const Block &other)
    {
        Box::operator=(other);
        m_margin = other.m_margin;
        m_padding = other.m_padding;
        m_minWidth = other.m_minWidth;
        m_maxWidth = other.m_maxWidth;
        m_minHeight = other.m_minHeight;
        m_maxHeight = other.m_maxHeight;
        return *this;
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
        setWidth(size.x);
        setHeight(size.y);
        return size;
    }

    sf::Vector2f Block::inflateBlock(const sf::Vector2f &containerSize)
    {
        auto hMargin = m_margin.getHorizontal();
        auto vMargin = m_margin.getVertical();
        sf::Vector2f size{std::max(getWidth(), std::min(containerSize.x, m_maxWidth + hMargin)),
                          std::max(getHeight(), std::min(containerSize.y, m_maxHeight + vMargin))};
        setWidth(size.x - hMargin);
        setHeight(size.y - vMargin);
        if (m_background)
            InflatableNode::inflate(*m_background, {getWidth(), getHeight()});
        return size;
    }

    void Block::placeBlock(const sf::Vector2f &position)
    {
        setLeft(position.x + m_margin.left);
        setTop(position.y + m_margin.top);
        if (m_background)
            InflatableNode::place(*m_background, {getLeft(), getTop()});
    }

    void Block::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Block::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Block::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
    }

    bool Block::onEvent(const sf::Event &event)
    {
        eventBlock(event);
        auto handled = eventChildren(event);
        return handled;
    }

    sf::Vector2f Block::onCompact()
    {
        auto size = compactBlock({0, 0});
        return size;
    }

    sf::Vector2f Block::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        return size;
    }

    void Block::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
    }

}