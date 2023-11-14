#ifndef CACTO_LINE_VIEWER_HPP
#define CACTO_LINE_VIEWER_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class Line;

    class CACTO_GRAPHICS_API LineViewer
        : public virtual sf::Drawable
    {

    public:
        const Line *const getLine() const;
        void setLine(const Line *const value);

        szt getPrecision() const;
        void setPrecision(szt value);

        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        bool isClosed() const;
        void setClosed(bool value = true);

        LineViewer();
        virtual ~LineViewer();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const Line *m_line;
        szt m_precision;
        sf::Color m_color;
        bool m_closed;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

}

#endif