#ifndef CACTO_UPDATE_NODE_HPP
#define CACTO_UPDATE_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class UpdateSignal;

    class CACTO_CORE_API UpdateNode
        : public virtual Node
    {

    public:
        bool handleSignal(Node *const target, const Signal &signal) override;
        void update(const sf::Time &time);

        UpdateNode();
        virtual ~UpdateNode();

    protected:
        virtual void onUpdate(const UpdateSignal &signal);
    };

}

#endif