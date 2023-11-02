#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Picture.hpp>

namespace cacto
{

    const Figure &Picture::getFigure() const
    {
        return m_figure;
    }

    Figure &Picture::getFigure()
    {
        return m_figure;
    }
    Picture::Picture(const sf::Texture &texture)
        : Block(),
          m_figure(texture)
    {
    }

    Picture::~Picture() = default;

    Picture::Picture(const Picture &other)
        : Block(other),
          m_figure(other.m_figure)
    {
    }

    Picture &Picture::operator=(const Picture &other)
    {
        m_figure = other.m_figure;
        return *this;
    }

    void Picture::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        target.draw(dynamic_cast<const DrawNode &>(m_figure), states);
    }

    sf::Vector2f Picture::onCompact()
    {
        auto contentSize = m_figure.compact();
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f Picture::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        auto contentBox = getContentBox();
        m_figure.inflate({contentBox.getWidth(), contentBox.getHeight()});
        return size;
    }

    void Picture::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        auto contentBox = getContentBox();
        m_figure.place({contentBox.getLeft(), contentBox.getTop()});
    }

}
