#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/UI/Figure.hpp>

namespace cacto
{

    Node *const Figure::getParent() const
    {
        return m_parent;
    }

    const sf::Texture &Figure::getTexture() const
    {
        return *m_texture;
    }

    void Figure::setTexture(const sf::Texture &value, bool resetRect)
    {
        m_texture = &value;
        m_invalid = true;
        if (resetRect)
            setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
    }

    const sf::FloatRect &Figure::getTextureRect() const
    {
        return m_textureRect;
    }

    void Figure::setTextureRect(const sf::FloatRect &value)
    {
        m_textureRect = value;
        m_invalid = true;
    }

    void Figure::update(bool force) const
    {
        if (m_invalid || force)
        {
            onUpdate();
            m_invalid = false;
        }
    }

    Figure::Figure(const sf::Texture &texture)
        : m_parent(),
          m_texture(&texture),
          m_textureRect(),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
        cacto::setPoints(m_array, Rectangle::Identity, 1);
        cacto::setColor(m_array, sf::Color::White);
        setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
    }

    Figure::~Figure()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

    Figure::Figure(const Figure &other)
        : m_parent(),
          m_texture(other.m_texture),
          m_textureRect(other.m_textureRect),
          m_invalid(true),
          m_array(sf::PrimitiveType::TriangleFan)
    {
        cacto::setPoints(m_array, Rectangle::Identity, 1);
        cacto::setColor(m_array, sf::Color::White);
    }

    Figure &Figure::operator=(const Figure &other)
    {
        m_texture = other.m_texture;
        m_textureRect = other.m_textureRect;
        m_invalid = true;
        m_array = sf::VertexArray{sf::PrimitiveType::TriangleFan};
        cacto::setPoints(m_array, Rectangle::Identity, 1);
        cacto::setColor(m_array, sf::Color::White);
        return *this;
    }

    void Figure::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Figure::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Figure::onUpdate() const
    {
        cacto::setTexCoords(m_array, m_textureRect);
        cacto::mapPositions(m_array, {{getLeft(), getTop()}, {getWidth(), getHeight()}});
    }

    void Figure::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update();
        if (getWidth() > 0 && getHeight() > 0)
        {
            auto _states = states;
            _states.texture = m_texture;
            target.draw(m_array, _states);
        }
        DrawNode::onDraw(target, states);
    }

    sf::Vector2f Figure::onCompact()
    {
        setWidth(0);
        setHeight(0);
        m_invalid = true;
        return {0, 0};
    }

    sf::Vector2f Figure::onInflate(const sf::Vector2f &containerSize)
    {
        setWidth(containerSize.x);
        setHeight(containerSize.y);
        m_invalid = true;
        return containerSize;
    }

    void Figure::onPlace(const sf::Vector2f &position)
    {
        setLeft(position.x);
        setTop(position.y);
        m_invalid = true;
    }

}