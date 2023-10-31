#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/UI/Picture.hpp>

namespace cacto
{

    Node *const Picture::getParent() const
    {
        return m_parent;
    }

    const Block &Picture::getBlock() const
    {
        return m_frame;
    }

    Block &Picture::getBlock()
    {
        return m_frame;
    }

    const Surface &Picture::getSurface() const
    {
        return m_surface;
    }

    Surface &Picture::getSurface()
    {
        return m_surface;
    }

    Picture::Anchor Picture::getHorizontalAnchor() const
    {
        auto anchor = m_frame.getHorizontalAnchor(m_surface);
        return anchor;
    }

    void Picture::setHorizontalAnchor(Anchor value)
    {
        m_frame.setHorizontalAnchor(m_surface, value);
    }

    Picture::Anchor Picture::getVerticalAnchor() const
    {
        auto anchor = m_frame.getVerticalAnchor(m_surface);
        return anchor;
    }

    void Picture::setVerticalAnchor(Anchor value)
    {
        m_frame.setVerticalAnchor(m_surface, value);
    }

    Picture::Picture()
        : m_parent(),
          m_frame(),
          m_surface()
    {
        m_frame.append(m_surface);
    }

    Picture::~Picture()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

    Picture::Picture(const Picture &other)
        : m_parent(),
          m_frame(other.m_frame),
          m_surface(other.m_surface)
    {
        m_frame.append(m_surface);
    }

    Picture &Picture::operator=(const Picture &other)
    {
        m_frame = other.m_frame;
        m_surface = other.m_surface;
        return *this;
    }

    void Picture::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Picture::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Picture::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(m_frame, states);
    }

    sf::Vector2f Picture::onCompact()
    {
        auto size = m_frame.compact();
        return size;
    }

    sf::Vector2f Picture::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = m_frame.inflate(containerSize);
        return size;
    }

    void Picture::onPlace(const sf::Vector2f &position)
    {
        m_frame.place(position);
    }

}