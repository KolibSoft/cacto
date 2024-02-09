#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Core/XmlPack.hpp>
#include <Cacto/Core/XmlUtils.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>
#include <Cacto/Window/NodeUtils.hpp>
#include <Cacto/UI/NodeUtils.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    Block &&Block::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Block &&Block::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Block &&Block::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Block &&Block::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Block &&Block::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Block &&Block::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Block &&Block::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Block &&Block::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    Reference<Node> Block::getBackground() const
    {
        return m_background.getInstance();
    }

    Block &&Block::setBackground(Reference<Node> value)
    {
        if (value)
        {
            if (value->getParent())
                throw std::runtime_error("The background can not have a parent");
            Node *current = this;
            while (current)
            {
                if (current == value.getInstance())
                    throw std::runtime_error("The background is its own block ancestor");
                current = current->getParent();
            }
        }
        m_background = std::move(value);
        return std::move(*this);
    }

    const Thickness &Block::getMargin() const
    {
        return m_margin;
    }

    Block &&Block::setMargin(const Thickness &value)
    {
        m_margin = value;
        return std::move(*this);
    }

    const Thickness &Block::getPadding() const
    {
        return m_padding;
    }

    Block &&Block::setPadding(const Thickness &value)
    {
        m_padding = value;
        return std::move(*this);
    }

    f32t Block::getMinWidth() const
    {
        return m_minWidth;
    }

    Block &&Block::setMinWidth(f32t value)
    {
        m_minWidth = value;
        return std::move(*this);
    }

    f32t Block::getMaxWidth() const
    {
        return m_maxWidth;
    }

    Block &&Block::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
        return std::move(*this);
    }

    f32t Block::getMinHeight() const
    {
        return m_minHeight;
    }

    Block &&Block::setMinHeight(f32t value)
    {
        m_minHeight = value;
        return std::move(*this);
    }

    f32t Block::getMaxHeight() const
    {
        return m_maxHeight;
    }

    Block &&Block::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
        return std::move(*this);
    }

    Block &&Block::setFixedWidth(f32t value)
    {
        m_minWidth = value;
        m_maxWidth = value;
        return std::move(*this);
    }

    Block &&Block::setFixedHeight(f32t value)
    {
        m_minHeight = value;
        m_maxHeight = value;
        return std::move(*this);
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

    const sf::Transform &Block::getVisualTransform() const
    {
        return m_vTransform;
    }

    const std::string &Block::getId() const
    {
        return m_id;
    }

    Block &&Block::setId(const std::string &value)
    {
        m_id = value;
        return std::move(*this);
    }

    Node *const Block::getParent() const
    {
        return m_parent;
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
        auto parent = m_parent;
        m_parent = nullptr;
        parent->remove(*this);
    }

    Block *Block::clone() const
    {
        auto block = new Block(*this);
        return block;
    }

    Block *Block::acquire()
    {
        auto block = new Block(std::move(*this));
        return block;
    }

    bool Block::handle(const sf::Event &event)
    {
        handleBlock(event);
        auto handled = cacto::handleChildren(*this, event);
        return handled;
    }

    bool Block::bubble(Node &target, const sf::Event &event)
    {
        auto handle = cacto::bubbleParent(*this, target, event);
        return handle;
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

    bool Block::containsVisualPoint(const sf::Vector2f &point) const
    {
        auto result = containsPoint(m_vTransform.getInverse().transformPoint(point));
        return result;
    }

    Block::Block()
        : Box(),
          m_background(),
          m_margin(0),
          m_padding(0),
          m_minWidth(0),
          m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0),
          m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_id(),
          m_parent(),
          m_vTransform(sf::Transform::Identity)
    {
    }

    Block::~Block()
    {
        detach();
    }

    Block::Block(const Block &other)
        : Block()
    {
        *this = other;
    }

    Block &Block::operator=(const Block &other)
    {
        clone(other);
        return *this;
    }

    Block::Block(Block &&other)
        : Block()
    {
        *this = std::move(other);
    }

    Block &Block::operator=(Block &&other)
    {
        acquire(std::move(other));
        other.detach();
        return *this;
    }

    void Block::clone(const Block &other)
    {
        Box::operator=(other);
        if (other.m_background)
            m_background = {other.m_background->clone(), true};
        m_margin = other.m_margin;
        m_padding = other.m_padding;
        m_minWidth = other.m_minWidth;
        m_maxWidth = other.m_maxWidth;
        m_minHeight = other.m_minHeight;
        m_maxHeight = other.m_maxHeight;
        m_id = other.m_id;
        m_vTransform = other.m_vTransform;
    }

    void Block::acquire(Block &&other)
    {
        Box::operator=(std::move(other));
        m_background = std::move(other.m_background);
        m_margin = std::move(other.m_margin);
        m_padding = std::move(other.m_padding);
        m_minWidth = other.m_minWidth;
        m_maxWidth = other.m_maxWidth;
        m_minHeight = other.m_minHeight;
        m_maxHeight = other.m_maxHeight;
        m_id = std::move(other.m_id);
        m_vTransform = std::move(other.m_vTransform);
        other.m_minWidth = 0;
        other.m_maxWidth = 0;
        other.m_minHeight = 0;
        other.m_maxHeight = 0;
    }

    void Block::drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background)
            cacto::draw(*m_background, target, states);
        m_vTransform = states.transform;
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
            cacto::compact(*m_background);
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
            cacto::inflate(*m_background, {getWidth(), getHeight()});
        return size;
    }

    void Block::placeBlock(const sf::Vector2f &position)
    {
        setLeft(position.x + m_margin.left);
        setTop(position.y + m_margin.top);
        if (m_background)
            cacto::place(*m_background, {getLeft(), getTop()});
    }

    void Block::handleBlock(const sf::Event &event)
    {
        if (m_background)
            cacto::handle(*m_background, event);
    }

    void Block::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
    }

    XmlValue toXml(const Block &block)
    {
        XmlValue xml{"Block", {}};
        xml["margin"] = toString(block.getMargin());
        xml["padding"] = toString(block.getPadding());
        xml["minWidth"] = std::to_string(block.getMinWidth());
        xml["maxWidth"] = std::to_string(block.getMaxWidth());
        xml["minHeight"] = std::to_string(block.getMinHeight());
        xml["maxHeight"] = std::to_string(block.getMaxHeight());
        xml["id"] = block.getId();
        auto bxml = toXml(block.getBackground().getInstance());
        auto bid = getId(bxml);
        if (bid != "")
            xml["background"] = "@xml/" + bid;
        else
        {
            bxml["isBackground"] = "true";
            xml.asTag().content.push_back(std::move(bxml));
        }
        return std::move(xml);
    }

    Block toBlock(const XmlValue &xml)
    {
        Block block{};
        block.setMargin(toTickness(xml.getAttribute("margin", "0,0,0,0")));
        block.setPadding(toTickness(xml.getAttribute("padding", "0,0,0,0")));
        block.setMinWidth(std::stof(xml.getAttribute("minWidth", "0")));
        block.setMaxWidth(std::stof(xml.getAttribute("maxWidth", "inf")));
        block.setMinHeight(std::stof(xml.getAttribute("minHeight", "0")));
        block.setMaxHeight(std::stof(xml.getAttribute("maxHeight", "inf")));
        block.setId(xml.getAttribute("id"));
        auto bxml = getXml(xml.getAttribute("background"));
        if (bxml != nullptr)
        {
            auto node = fromXml<Node>(bxml);
            if (node)
                block.setBackground({node, true});
            else
                delete node;
        }
        else
            for (auto &ixml : xml.asTag().content)
                if (ixml["isBackground"] == "true")
                {
                    auto node = fromXml<Node>(xml[0]);
                    if (node)
                        block.setBackground({node, true});
                    else
                        delete node;
                    break;
                }
        return std::move(block);
    }

    namespace block
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Block *block = nullptr;
            if (value && typeid(*value) == typeid(Block) && (block = dynamic_cast<const Block *>(value)))
            {
                auto xml = cacto::toXml(*block);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Block")
            {
                auto block = new Block();
                *block = toBlock(xml);
                return block;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}