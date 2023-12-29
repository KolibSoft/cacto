#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Line.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/Graphics/LineViewer.hpp>

namespace cacto
{

    const Line *const LineViewer::getLine() const
    {
        return m_line;
    }

    void LineViewer::setLine(const Line *const value)
    {
        m_line = value;
        m_invalid = true;
    }

    szt LineViewer::getPrecision() const
    {
        return m_precision;
    }

    void LineViewer::setPrecision(szt value)
    {
        m_precision = value;
        m_invalid = true;
    }

    const sf::Color &LineViewer::getColor() const
    {
        return m_color;
    }

    void LineViewer::setColor(const sf::Color &value)
    {
        m_color = value;
        m_invalid = true;
    }

    bool LineViewer::isClosed() const
    {
        return m_closed;
    }

    void LineViewer::setClosed(bool value)
    {
        m_closed = value;
        m_invalid = true;
    }

    LineViewer::LineViewer()
        : m_line(nullptr),
          m_precision(1),
          m_color(sf::Color::White),
          m_closed(false),
          m_invalid(true),
          m_array(sf::PrimitiveType::LineStrip)
    {
    }

    LineViewer::~LineViewer() = default;

    void LineViewer::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_line)
        {
            if (m_invalid)
            {
                setPoints(m_array, *m_line, m_precision);
                cacto::setColor(m_array, m_color);
                if (m_closed)
                    m_array.append(m_array[0]);
                m_invalid = false;
            }
            target.draw(m_array, states);
        }
    }

}