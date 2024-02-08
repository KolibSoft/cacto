#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/RectUtils.hpp>
#include <Cacto/UI/Picture.hpp>

namespace cacto
{

    Picture &&Picture::setLeft(f32t value, bool resize)
    {
        Box::setLeft(value, resize);
        return std::move(*this);
    }

    Picture &&Picture::setRight(f32t value, bool resize)
    {
        Box::setRight(value, resize);
        return std::move(*this);
    }

    Picture &&Picture::setTop(f32t value, bool resize)
    {
        Box::setTop(value, resize);
        return std::move(*this);
    }

    Picture &&Picture::setBottom(f32t value, bool resize)
    {
        Box::setBottom(value, resize);
        return std::move(*this);
    }

    Picture &&Picture::setWidth(f32t value, BoxAnchor anchor)
    {
        Box::setWidth(value, anchor);
        return std::move(*this);
    }

    Picture &&Picture::setHeight(f32t value, BoxAnchor anchor)
    {
        Box::setHeight(value, anchor);
        return std::move(*this);
    }

    Picture &&Picture::shrink(const Thickness &thickness)
    {
        Box::shrink(thickness);
        return std::move(*this);
    }

    Picture &&Picture::expand(const Thickness &thickness)
    {
        Box::expand(thickness);
        return std::move(*this);
    }

    Picture &&Picture::setBackground(Node *const value)
    {
        Block::setBackground(value);
        return std::move(*this);
    }

    Picture &&Picture::setBackground(Node &&value)
    {
        Block::setBackground(std::move(value));
        return std::move(*this);
    }

    Picture &&Picture::setMargin(const Thickness &value)
    {
        Block::setMargin(value);
        return std::move(*this);
    }

    Picture &&Picture::setPadding(const Thickness &value)
    {
        Block::setPadding(value);
        return std::move(*this);
    }

    Picture &&Picture::setMinWidth(f32t value)
    {
        Block::setMinWidth(value);
        return std::move(*this);
    }

    Picture &&Picture::setMaxWidth(f32t value)
    {
        Block::setMaxWidth(value);
        return std::move(*this);
    }

    Picture &&Picture::setMinHeight(f32t value)
    {
        Block::setMinHeight(value);
        return std::move(*this);
    }

    Picture &&Picture::setMaxHeight(f32t value)
    {
        Block::setMaxHeight(value);
        return std::move(*this);
    }

    Picture &&Picture::setFixedWidth(f32t value)
    {
        Block::setFixedWidth(value);
        return std::move(*this);
    }

    Picture &&Picture::setFixedHeight(f32t value)
    {
        Block::setFixedHeight(value);
        return std::move(*this);
    }

    Picture::operator const Surface &() const
    {
        return m_surface;
    }

    Picture::operator Surface &()
    {
        return m_surface;
    }

    Picture &&Picture::setGeometry(const Geometry *const value)
    {
        m_surface.setGeometry(value);
        return std::move(*this);
    }

    Picture &&Picture::setPrecision(szt value)
    {
        m_surface.setPrecision(value);
        return std::move(*this);
    }

    Picture &&Picture::setColor(const sf::Color &value)
    {
        m_surface.setColor(value);
        return std::move(*this);
    }

    Picture &&Picture::setTexture(const sf::Texture *const value, bool resetRect)
    {
        m_surface.setTexture(value, resetRect);
        return std::move(*this);
    }

    PictureScale Picture::getScale() const
    {
        return m_scale;
    }

    Picture &&Picture::setScale(PictureScale value)
    {
        m_scale = value;
        return std::move(*this);
    }

    const sf::FloatRect &Picture::getTextureRect() const
    {
        return m_textureRect;
    }

    Picture &&Picture::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        return std::move(*this);
    }

    BoxAnchor Picture::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    Picture &&Picture::setHorizontalAnchor(BoxAnchor value)
    {
        m_hAnchor = value;
        return std::move(*this);
    }

    BoxAnchor Picture::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    Picture &&Picture::setVerticalAnchor(BoxAnchor value)
    {
        m_vAnchor = value;
        return std::move(*this);
    }

    Picture &&Picture::setId(const std::string &id)
    {
        Block::setId(id);
        return std::move(*this);
    }

    Picture *Picture::clone() const
    {
        auto picture = new Picture(*this);
        return picture;
    }

    Picture *Picture::acquire()
    {
        auto picture = new Picture(std::move(*this));
        return picture;
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
        if (m_scale == PictureScale::Fit)
        {
            auto fit = fitSize({m_textureRect.width, m_textureRect.height}, {contentBox.getWidth(), contentBox.getHeight()});
            contentBox.setWidth(fit.x, m_hAnchor);
            contentBox.setHeight(fit.y, m_vAnchor);
        }
        m_surface.inflate({contentBox.getWidth(), contentBox.getHeight()});
        if (m_scale == PictureScale::Crop)
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
        if (m_scale == PictureScale::Fit)
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
          m_scale(PictureScale::Fill),
          m_textureRect(),
          m_hAnchor(BoxAnchor::Start),
          m_vAnchor(BoxAnchor::Start)
    {
    }

    Picture::~Picture() = default;

    Picture::Picture(const Picture &other)
        : Picture()
    {
        *this = other;
    }

    Picture &Picture::operator=(const Picture &other)
    {
        m_surface = other.m_surface;
        m_scale = other.m_scale;
        m_textureRect = other.m_textureRect;
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        Block::operator=(other);
        return *this;
    }

    Picture::Picture(Picture &&other)
        : Picture()
    {
        *this = std::move(other);
    }

    Picture &Picture::operator=(Picture &&other)
    {
        m_surface = std::move(other.m_surface);
        m_scale = other.m_scale;
        m_textureRect = std::move(other.m_textureRect);
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        Block::operator=(std::move(other));
        return *this;
    }

    void Picture::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(m_surface, states);
    }

    std::string toString(PictureScale scale)
    {
        if (scale == PictureScale::Fill)
            return "Fill";
        else if (scale == PictureScale::Fit)
            return "Fit";
        else if (scale == PictureScale::Crop)
            return "Crop";
        else
            throw std::runtime_error("Invalid scale type");
    }

    PictureScale toPictureScale(const std::string &string)
    {
        if (string == "Fill")
            return PictureScale::Fill;
        else if (string == "Fit")
            return PictureScale::Fit;
        else if (string == "Crop")
            return PictureScale::Crop;
        else
            throw std::runtime_error("Invalid scale type");
    }

    XmlValue toXml(const Picture &picture)
    {
        XmlValue xml{"Picture", {}};
        xml |= toXml((const Block &)picture);
        xml |= toXml((const Surface &)picture);
        xml["scale"] = toString(picture.getScale());
        xml["textureRect"] = toString(picture.getTextureRect());
        xml["horizontalAnchor"] = toString(picture.getHorizontalAnchor());
        xml["verticalAnchor"] = toString(picture.getVerticalAnchor());
        return std::move(xml);
    }

    Picture toPicture(const XmlValue &xml)
    {
        Picture picture{};
        (Block &)picture = toBlock(xml);
        (Surface &)picture = toSurface(xml);
        picture.setScale(toPictureScale(xml.getAttribute("scale", "Fill")));
        picture.setTextureRect(toRect(xml.getAttribute("textureRect", "0,0,0,0")));
        picture.setHorizontalAnchor(toBoxAnchor(xml.getAttribute("horizontalAnchor", "Start")));
        picture.setVerticalAnchor(toBoxAnchor(xml.getAttribute("verticalAnchor", "Start")));
        return std::move(picture);
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
                auto picture = new Picture();
                *picture = toPicture(xml);
                return picture;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}
