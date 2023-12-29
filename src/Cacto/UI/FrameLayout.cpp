#include <stdexcept>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

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

    ParentNode *const FrameLayout::getParent() const
    {
        return Block::getParent();
    }

    szt FrameLayout::getChildCount() const
    {
        return m_child != nullptr ? 1 : 0;
    }

    ChildNode *const FrameLayout::getChild(szt index) const
    {
        if (index >= 1)
            return nullptr;
        return m_child;
    }

    void FrameLayout::append(ChildNode &child)
    {
        if (m_child == &child)
            return;
        if (m_child != nullptr)
            throw std::runtime_error("This node has already another child");
        if (child.getParent() != nullptr && child.getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
        if (hasAncestor(child))
            throw std::runtime_error("The node is an ancestor");
        m_child = &child;
        child.attach(*this);
    }

    void FrameLayout::remove(ChildNode &child)
    {
        if (m_child == &child)
        {
            m_child = nullptr;
            child.detach();
        }
    }

    void FrameLayout::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        if (m_child)
            cacto::draw(*m_child, target, states);
    }

    sf::Vector2f FrameLayout::compact()
    {
        auto childSize = m_child ? cacto::compact(*m_child) : sf::Vector2f{0, 0};
        m_childBox.setWidth(childSize.x);
        m_childBox.setHeight(childSize.y);
        auto size = compactBlock(childSize);
        return size;
    }

    sf::Vector2f FrameLayout::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_child)
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
        if (m_child)
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
          m_hAnchor(Start),
          m_vAnchor(Start),
          m_childBox(),
          m_child()
    {
    }

    FrameLayout::~FrameLayout()
    {
        if (m_child)
            remove(*m_child);
    }

    const Box &FrameLayout::getChildBox() const
    {
        return m_childBox;
    }

    XmlValue toXml(const FrameLayout &frame)
    {
        auto xml = cacto::toXml((const Block &)frame);
        xml.setName("FrameLayout");
        auto child = frame.getChild();
        if (child)
        {
            auto child_xml = toXml(child);
            xml.asContent().push_back(std::move(child_xml));
        }
        xml["horizontalAnchor"] = toString(frame.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(frame.getVerticalAnchor());
        return std::move(xml);
    }

    void fromXml(FrameLayout &frame, const XmlValue &xml)
    {
        frame.clearChildren();
        cacto::fromXml((Block &)frame, xml);
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                Node *node = nullptr;
                fromXml(node, item);
                auto child = dynamic_cast<ChildNode *>(node);
                if (child)
                    frame.append(*child);
            }
        Box::Anchor hAnchor{};
        Box::Anchor vAnchor{};
        cacto::fromString(hAnchor, xml.getAttribute("horizontalAnchor", "Start"));
        cacto::fromString(vAnchor, xml.getAttribute("verticalAnchor", "Start"));
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
                auto frame = std::make_shared<FrameLayout>();
                cacto::fromXml(*frame, xml);
                Node::XmlStack.push(frame);
                return frame.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}