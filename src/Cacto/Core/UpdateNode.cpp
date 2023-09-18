#include <Cacto/Core/UpdateSignal.hpp>
#include <Cacto/Core/UpdateNode.hpp>

namespace cacto
{

    bool UpdateNode::handleSignal(Node *const target, const Signal &signal)
    {
        if (!target)
        {
            auto *updateSignal = dynamic_cast<const UpdateSignal *>(&signal);
            if (updateSignal)
            {
                onUpdate(*updateSignal);
                return true;
            }
        }
        return false;
    }

    void UpdateNode::update(const sf::Time &time)
    {
        UpdateSignal signal{time};
        onUpdate(signal);
    }

    void UpdateNode::onUpdate(const UpdateSignal &signal)
    {
        auto handled = bubbleSignal(this, signal);
    }

    UpdateNode::UpdateNode() = default;

    UpdateNode::~UpdateNode() = default;

}