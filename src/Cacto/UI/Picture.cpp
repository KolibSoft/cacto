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

    void Picture::setScale(Scale value)
    {
        m_scale = value;
    }

    const sf::FloatRect &Picture::getTextureRect() const
    {
        return m_textureRect;
    }

    void Picture::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
    }

    Picture::Anchor Picture::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void Picture::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    Picture::Anchor Picture::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void Picture::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    const Surface &Picture::getSurface() const
    {
        return m_surface;
    }

    Surface &Picture::getSurface()
    {
        return m_surface;
    }

    Picture::Picture(const sf::Texture &texture, Scale scale)
        : Block(),
          m_surface(Rectangle::Identity, sf::Color::White, &texture),
          m_scale(scale),
          m_textureRect(),
          m_hAnchor(Start),
          m_vAnchor(Start)
    {
        m_textureRect = m_surface.getTextureRect();
    }

    Picture::~Picture() = default;

    Picture::Picture(const Picture &other)
        : Block(other),
          m_surface(other.m_surface),
          m_scale(other.m_scale),
          m_textureRect(other.m_textureRect),
          m_hAnchor(other.m_hAnchor),
          m_vAnchor(other.m_vAnchor)
    {
        m_textureRect = m_surface.getTextureRect();
    }

    Picture &Picture::operator=(const Picture &other)
    {
        m_surface = other.m_surface;
        m_scale = other.m_scale;
        m_textureRect = other.m_textureRect;
        m_hAnchor = other.m_hAnchor;
        m_vAnchor = other.m_vAnchor;
        return *this;
    }

    void Picture::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(dynamic_cast<const DrawNode &>(m_surface), states);
    }

    sf::Vector2f Picture::onCompact()
    {
        auto contentSize = m_surface.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Picture::onInflate(const sf::Vector2f &containerSize)
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

    void Picture::onPlace(const sf::Vector2f &position)
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

}
