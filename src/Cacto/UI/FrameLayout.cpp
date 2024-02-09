#include <stdexcept>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>
#include <Cacto/Window/NodeUtils.hpp>
#include <Cacto/UI/NodeUtils.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    FrameLayout &&FrameLayout::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setBackground(Reference<Node> value)
    {
        Block::setBackground(std::move(value));
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setMargin(const Thickness &value)
    {
        Block::setMargin(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setPadding(const Thickness &value)
    {
        Block::setPadding(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setMinWidth(f32t value)
    {
        Block::setMinWidth(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setMaxWidth(f32t value)
    {
        Block::setMaxWidth(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setMinHeight(f32t value)
    {
        Block::setMinHeight(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setMaxHeight(f32t value)
    {
        Block::setMaxHeight(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setFixedWidth(f32t value)
    {
        Block::setFixedWidth(value);
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setFixedHeight(f32t value)
    {
        Block::setFixedHeight(value);
        return std::move(*this);
    }

    BoxAnchor FrameLayout::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    FrameLayout &&FrameLayout::setHorizontalAnchor(BoxAnchor value)
    {
        m_hAnchor = value;
        return std::move(*this);
    }

    BoxAnchor FrameLayout::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    FrameLayout &&FrameLayout::setVerticalAnchor(BoxAnchor value)
    {
        m_vAnchor = value;
        return std::move(*this);
    }

    FrameLayout &&FrameLayout::setId(const std::string &value)
    {
        Block::setId(value);
        return std::move(*this);
    }

    Node *const FrameLayout::getParent() const
    {
        return Block::getParent();
    }

    FrameLayout *FrameLayout::clone() const
    {
        auto layout = new FrameLayout(*this);
        return layout;
    }

    FrameLayout *FrameLayout::acquire()
    {
        auto layout = new FrameLayout(std::move(*this));
        return layout;
    }

    szt FrameLayout::getChildCount() const
    {
        return m_child != nullptr ? 1 : 0;
    }

    ChildNode *const FrameLayout::getChild(szt index) const
    {
        if (index >= 1)
            return nullptr;
        return m_child.getInstance();
    }

    void FrameLayout::append(ChildNode &child)
    {
        append(Reference(child));
    }

    FrameLayout &&FrameLayout::append(Reference<ChildNode> child)
    {
        if (m_child == child)
            return std::move(*this);
        if (m_child != nullptr)
            throw std::runtime_error("This node has already another child");
        if (child->getParent() != nullptr && child->getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
        if (hasAncestor(*child))
            throw std::runtime_error("The node is an ancestor");
        m_child = std::move(child);
        m_child->attach(*this);
        return std::move(*this);
    }

    void FrameLayout::remove(ChildNode &child)
    {
        if (m_child == &child)
        {
            auto _child = std::move(m_child);
            _child->detach();
        }
    }

    sf::Vector2f FrameLayout::compact()
    {
        auto childSize = m_child != nullptr ? cacto::compact(*m_child) : sf::Vector2f{0, 0};
        m_childBox.setWidth(childSize.x);
        m_childBox.setHeight(childSize.y);
        auto size = compactBlock(childSize);
        return size;
    }

    sf::Vector2f FrameLayout::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_child != nullptr)
        {
            auto contentBox = getContentBox();
            auto childSize = cacto::inflate(*m_child, {contentBox.getWidth(), contentBox.getHeight()});
            m_childBox.setWidth(childSize.x);
            m_childBox.setHeight(childSize.y);
        }
        return size;
    }

    void FrameLayout::place(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (m_child != nullptr)
        {
            auto contentBox = getContentBox();
            contentBox.setWidth(m_childBox.getWidth(), m_hAnchor);
            contentBox.setHeight(m_childBox.getHeight(), m_vAnchor);
            sf::Vector2f childPlace{contentBox.getLeft(), contentBox.getTop()};
            cacto::place(*m_child, childPlace);
            m_childBox.setLeft(childPlace.x);
            m_childBox.setTop(childPlace.y);
        }
    }

    FrameLayout::FrameLayout()
        : Block(),
          m_hAnchor(BoxAnchor::Start),
          m_vAnchor(BoxAnchor::Start),
          m_childBox(),
          m_child()
    {
    }

    FrameLayout::~FrameLayout() = default;

    FrameLayout::FrameLayout(const FrameLayout &other)
        : FrameLayout()
    {
        *this = other;
    }

    FrameLayout &FrameLayout::operator=(const FrameLayout &other)
    {
        clone(other);
        return *this;
    }

    FrameLayout::FrameLayout(FrameLayout &&other)
        : FrameLayout()
    {
        *this = std::move(other);
    }

    FrameLayout &FrameLayout::operator=(FrameLayout &&other)
    {
        acquire(std::move(other));
        other.detach();
        return *this;
    }

    void FrameLayout::clone(const FrameLayout &other)
    {
        clearChildren();
        Block::clone(other);
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        m_childBox = other.m_childBox;
        if (other.m_child != nullptr)
            append({other.m_child->clone(), true});
    }

    void FrameLayout::acquire(FrameLayout &&other)
    {
        clearChildren();
        Block::acquire(std::move(other));
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        m_childBox = std::move(other.m_childBox);
        m_child = std::move(other.m_child);
        other.m_child = nullptr;
        m_child->detach();
        m_child->attach(*this);
    }

    const Box &FrameLayout::getChildBox() const
    {
        return m_childBox;
    }

    void FrameLayout::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        if (m_child != nullptr)
            cacto::draw(*m_child, target, states);
    }

    XmlValue toXml(const FrameLayout &frame)
    {
        XmlValue xml{"FrameLayout", {}};
        xml |= toXml((const Block &)frame);
        xml["horizontalAnchor"] = toString(frame.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(frame.getVerticalAnchor());
        auto child = frame.getChild();
        if (child)
        {
            auto cxml = toXml<Node>(child);
            xml.append(cxml);
        }
        return std::move(xml);
    }

    FrameLayout toFrameLayout(const XmlValue &xml)
    {
        FrameLayout frame{};
        (Block &)frame = toBlock(xml);
        frame.setHorizontalAnchor(toBoxAnchor(xml.getAttribute("horizontalAnchor", "Start")));
        frame.setVerticalAnchor(toBoxAnchor(xml.getAttribute("verticalAnchor", "Start")));
        for (auto &ixml : xml.asTag().content)
            if (ixml["isBackground"] == "")
            {
                auto node = fromXml<Node>(ixml);
                if (node)
                {
                    auto child = dynamic_cast<ChildNode *>(node);
                    if (child)
                        frame.append({child, true});
                    else
                        delete node;
                }

                break;
            }
        return std::move(frame);
    }

    namespace frame
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const FrameLayout *frame = nullptr;
            if (value && typeid(*value) == typeid(FrameLayout) && (frame = dynamic_cast<const FrameLayout *>(value)))
            {
                auto xml = cacto::toXml(*frame);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "FrameLayout")
            {
                auto frame = new FrameLayout();
                *frame = toFrameLayout(xml);
                return frame;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}