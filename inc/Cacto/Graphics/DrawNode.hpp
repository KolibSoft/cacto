#ifndef CACTO_DRAW_NODE_HPP
#define CACTO_DRAW_NODE_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class RenderTarget;
    class RenderStates;
}

namespace cacto
{

    class DrawSignal;

    class CACTO_GRAPHICS_API DrawNode
        : public virtual Node
    {

    public:
        virtual bool handleSignal(Node *const target, const Signal &signal);
        void draw(sf::RenderTarget &target, const sf::RenderStates &states);

        DrawNode();
        virtual ~DrawNode();

    protected:
        virtual bool onDraw(Node *const target, const DrawSignal &signal);
    };

}

#endif