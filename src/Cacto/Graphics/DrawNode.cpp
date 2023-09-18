#include <Cacto/Graphics/DrawSignal.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    bool DrawNode::handleSignal(Node *const target, const Signal &signal)
    {
        if (!target)
        {
            auto drawSignal = dynamic_cast<const DrawSignal *>(&signal);
            if (drawSignal)
            {
                onDraw(*drawSignal);
                return true;
            }
        }
        return false;
    }

    void DrawNode::draw(sf::RenderTarget &target, const sf::RenderStates &states)
    {
        DrawSignal signal{target, states};
        onDraw(signal);
    }

    void DrawNode::onDraw(const DrawSignal &signal)
    {
        auto handled = bubbleSignal(this, signal);
    }

    DrawNode::DrawNode() = default;

    DrawNode::~DrawNode() = default;

}