#include <Cacto/Graphics/DrawSignal.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    bool DrawNode::handleSignal(Node *const target, const Signal &signal)
    {
        auto drawSignal = dynamic_cast<const DrawSignal *>(&signal);
        auto handled = drawSignal && onDraw(target, *drawSignal);
        return handled;
    }

    void DrawNode::draw(sf::RenderTarget &target, const sf::RenderStates &states)
    {
        DrawSignal signal{target, states};
        onDraw(this, signal);
    }

    bool DrawNode::onDraw(Node *const target, const DrawSignal &signal)
    {
        auto handled = bubbleSignal(target, signal);
        return handled;
    }

    DrawNode::DrawNode() = default;

    DrawNode::~DrawNode() = default;

}