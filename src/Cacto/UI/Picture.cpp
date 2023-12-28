#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Picture.hpp>

namespace cacto
{

    Picture::Scale Picture::getScale() const
    {
        return m_scale;
    }

    Picture &Picture::setScale(Scale value)
    {
        m_scale = value;
        return *this;
    }

    const sf::FloatRect &Picture::getTextureRect() const
    {
        return m_textureRect;
    }

    Picture &Picture::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        return *this;
    }

    Picture::Anchor Picture::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    Picture &Picture::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
        return *this;
    }

    Picture::Anchor Picture::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    Picture &Picture::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
        return *this;
    }

    const Surface &Picture::asSurface() const
    {
        return m_surface;
    }

    Surface &Picture::asSurface()
    {
        return m_surface;
    }

    void Picture::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(m_surface, states);
    }

    sf::Vector2f Picture::compact()
    {
        auto contentSize = m_surface.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Picture::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        auto contentBox = getContentBox();
        if (m_scale == Fit)
        {
            auto fit = fitSize({m_textureRect.width, m_textureRect.height}, {contentBox.getWidth(), contentBox.getHeight()});
            contentBox.setWidth(fit.x, m_hAnchor);
            contentBox.setHeight(fit.y, m_vAnchor);
        }
        m_surface.inflate({contentBox.getWidth(), contentBox.getHeight()});
        if (m_scale == Crop)
        {
            auto crop = fitSize({contentBox.getWidth(), contentBox.getHeight()}, {m_textureRect.width, m_textureRect.height});
            Box box = m_textureRect;
            box.setWidth(crop.x, m_hAnchor);
            box.setHeight(crop.y, m_vAnchor);
            m_surface.setTextureRect(box);
        }
        else
        {
            m_surface.setTextureRect(m_textureRect);
        }
        return size;
    }

    void Picture::place(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        if (m_scale == Fit)
        {
            auto childSize = fitSize({m_textureRect.width, m_textureRect.height}, {contentBox.getWidth(), contentBox.getHeight()});
            contentBox.setWidth(childSize.x, m_hAnchor);
            contentBox.setHeight(childSize.y, m_vAnchor);
        }
        m_surface.place({contentBox.getLeft(), contentBox.getTop()});
    }

    Picture::Picture()
        : Block(),
          m_surface(),
          m_scale(Fill),
          m_textureRect(),
          m_hAnchor(Start),
          m_vAnchor(Start)
    {
        m_textureRect = m_surface.getTextureRect();
    }

    Picture::~Picture() = default;

    XmlValue CACTO_UI_API toXml(const Picture &picture)
    {
        auto xml = cacto::toXml((const Block &)picture);
        xml.setName("Picture");
        auto surface_xml = cacto::toXml(picture.asSurface());
        for (auto &pair : surface_xml.asAttributes())
            xml[pair.first] = pair.second;
        xml["horizontalAnchor"] = toString(picture.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(picture.getVerticalAnchor());
        return std::move(xml);
    }

    void CACTO_UI_API fromXml(Picture &picture, const XmlValue &xml)
    {
        cacto::fromXml((Block &)picture, xml);
        cacto::fromXml(picture.asSurface(), xml);
        Box::Anchor hAnchor{};
        Box::Anchor vAnchor{};
        cacto::fromString(hAnchor, xml.getAttribute("horizontalAnchor", "Start"));
        cacto::fromString(vAnchor, xml.getAttribute("verticalAnchor", "Start"));
    }

    namespace picture
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Picture *picture = nullptr;
            if (value && typeid(*value) == typeid(Picture) && (picture = dynamic_cast<const Picture *>(value)))
            {
                auto xml = cacto::toXml(*picture);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Picture")
            {
                auto picture = std::make_shared<Picture>();
                cacto::fromXml(*picture, xml);
                Node::XmlStack.push(picture);
                return picture.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}
