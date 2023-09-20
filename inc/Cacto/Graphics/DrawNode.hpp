#ifndef CACTO_DRAW_NODE_HPP
#define CACTO_DRAW_NODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class RenderTarget;
    class RenderStates;
}

namespace cacto
{

    class CACTO_GRAPHICS_API DrawNode
        : public virtual sf::Drawable,
          public virtual Node
    {

    public:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        DrawNode();
        virtual ~DrawNode();

        static void draw(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states);

    protected:
        virtual bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;
    };

}

#endif