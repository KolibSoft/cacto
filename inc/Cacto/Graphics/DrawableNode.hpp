#ifndef CACTO_DRAWABLE_NODE_HPP
#define CACTO_DRAWABLE_NODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class DrawSignal;

    class CACTO_GRAPHICS_API DrawableNode
        : public virtual sf::Drawable,
          public virtual Node
    {

    public:
        bool handleSignal(Node *const target, const Signal &signal) override;

        DrawableNode() = default;
        virtual ~DrawableNode() = default;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        virtual void onDraw(const DrawSignal &signal) const;
    };

}

#endif