#include <Cacto/Animations/UpdateSignal.hpp>
#include <Cacto/Animations/UpdateNode.hpp>

namespace cacto
{

    bool UpdateNode::handleSignal(Node *const target, const Signal &signal)
    {
        auto *updateSignal = dynamic_cast<const UpdateSignal *>(&signal);
        auto handled = updateSignal && onUpdate(target, *updateSignal);
        return handled;
    }

    void UpdateNode::update(const sf::Time &time)
    {
        UpdateSignal signal{time};
        onUpdate(this, signal);
    }

    bool UpdateNode::onUpdate(Node *const target, const UpdateSignal &signal)
    {
        auto handled = target ? bubbleSignal(target, signal) : dispatchSignal(target, signal);
        return handled;
    }

    UpdateNode::UpdateNode() = default;

    UpdateNode::~UpdateNode() = default;

}