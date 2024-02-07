#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    Label::Anchor Label::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    Label &Label::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
        return *this;
    }

    Label::Anchor Label::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    Label &Label::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
        return *this;
    }

    const Span &Label::asSpan() const
    {
        return m_span;
    }

    Span &Label::asSpan()
    {
        return m_span;
    }

    void Label::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(m_span, states);
    }

    sf::Vector2f Label::compact()
    {
        auto contentSize = m_span.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Label::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        auto contentBox = getContentBox();
        m_span.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void Label::place(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        contentBox.setWidth(m_span.getWidth(), m_hAnchor);
        contentBox.setHeight(m_span.getHeight(), m_vAnchor);
        m_span.place({contentBox.getLeft(), contentBox.getTop()});
    }

    Label::Label()
        : Block(),
          m_span(),
          m_hAnchor(BoxAnchor::Start),
          m_vAnchor(BoxAnchor::Start)
    {
    }

    Label::~Label() = default;

    XmlValue CACTO_UI_API toXml(const Label &label)
    {
        auto xml = cacto::toXml((const Block &)label);
        xml.setName("Label");
        auto span_xml = cacto::toXml(label.asSpan());
        for (auto &pair : span_xml.asAttributes())
            xml[pair.first] = pair.second;
        xml["horizontalAnchor"] = toString(label.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(label.getVerticalAnchor());
        return std::move(xml);
    }

    void CACTO_UI_API fromXml(Label &label, const XmlValue &xml)
    {
        cacto::fromXml((Block &)label, xml);
        cacto::fromXml(label.asSpan(), xml);
        Box::BoxAnchor hAnchor{};
        Box::BoxAnchor vAnchor{};
        cacto::fromString(hAnchor, xml.getAttribute("horizontalAnchor", "Start"));
        cacto::fromString(vAnchor, xml.getAttribute("verticalAnchor", "Start"));
    }

    namespace label
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Label *label = nullptr;
            if (value && typeid(*value) == typeid(Label) && (label = dynamic_cast<const Label *>(value)))
            {
                auto xml = cacto::toXml(*label);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Label")
            {
                auto label = std::make_shared<Label>();
                cacto::fromXml(*label, xml);
                Node::XmlStack.push(label);
                return label.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}