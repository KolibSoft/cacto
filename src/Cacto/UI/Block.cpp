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

    ParentNode *const Block::getParent() const
    {
        return m_parent;
    }

    void Block::drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        m_vTransform = states.transform;
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
        setLeft(position.x + m_margin.left);
        setTop(position.y + m_margin.top);
        if (m_background)
            InflatableNode::place(*m_background, {getLeft(), getTop()});
    }

    bool Block::containsVisually(const sf::Vector2f &point) const
    {
        auto result = contains(m_vTransform.getInverse().transformPoint(point));
        return result;
    }

    Block::Block()
        : Box(),
          m_id(),
          m_background(nullptr),
          m_margin(0),
          m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_parent(),
          m_vTransform(sf::Transform::Identity)
    {
    }

    Block::~Block()
    {
        detach();
    }

    XmlValue toXml(const Block &block)
    {
        XmlValue xml{"Block", {}};
        auto background = block.getBackground();
        if (background)
        {
            XmlValue content{"Background", {}};
            auto background_xml = toXml(background);
            content.asContent().push_back(background_xml);
            xml.asContent().push_back(std::move(content));
        }
        xml["id"] = block.getId();
        xml["margin"] = toString(block.getMargin());
        xml["padding"] = toString(block.getPadding());
        xml["minWidth"] = std::to_string(block.getMinWidth());
        xml["maxWidth"] = std::to_string(block.getMaxWidth());
        xml["minHeight"] = std::to_string(block.getMinHeight());
        xml["maxHeight"] = std::to_string(block.getMaxHeight());
        return std::move(xml);
    }

    void fromXml(Block &block, const XmlValue &xml)
    {
        block.setBackground(nullptr);
        auto id = xml.getAttribute("id");
        if (xml.isTag())
            for (auto &item : xml.asContent())
                if (item.isTag() && item.getName() == "Background")
                    for (auto &background_xml : item.asContent())
                    {
                        Node *node = nullptr;
                        fromXml(node, background_xml);
                        ChildNode *child = dynamic_cast<ChildNode *>(node);
                        if (child)
                            block.setBackground(child);
                    }
        Thickness margin{};
        Thickness padding{};
        auto minWidth = std::stof(xml.getAttribute("minWidth", "0"));
        auto maxWidth = std::stof(xml.getAttribute("maxWidth", "inf"));
        auto minHeight = std::stof(xml.getAttribute("minHeight", "0"));
        auto maxHeight = std::stof(xml.getAttribute("maxHeight", "inf"));
        fromString(margin, xml.getAttribute("margin", "0,0,0,0"));
        fromString(padding, xml.getAttribute("padding", "0,0,0,0"));
        block
            .setId(id)
            .setMargin(margin)
            .setPadding(padding)
            .setMinWidth(minWidth)
            .setMaxWidth(maxWidth)
            .setMinHeight(minHeight)
            .setMaxHeight(maxHeight);
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
                auto block = std::make_shared<Block>();
                cacto::fromXml(*block, xml);
                Node::XmlStack.push(block);
                return block.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}