#include <Cacto/Graphics/DrawSignal.hpp>
#include <Cacto/Graphics/DrawableNode.hpp>

namespace cacto
{

    bool DrawableNode::handleSignal(Node *const target, const Signal &signal)
    {
        if (!target)
        {
            auto drawSignal = dynamic_cast<const DrawSignal *>(&signal);
            if (drawSignal)
                onDraw(*drawSignal);
        }
    }

    void DrawableNode::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        DrawSignal signal{target, states};
        onDraw(signal);
    }

    void DrawableNode::onDraw(const DrawSignal &signal) const
    {
        auto *mut = const_cast<DrawableNode *>(this);
        mut->bubbleSignal(mut, signal);
    }

}