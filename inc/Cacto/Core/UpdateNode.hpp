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
        virtual bool handleSignal(Node *const target, const Signal &signal);
        void update(const sf::Time &time);

        UpdateNode();
        virtual ~UpdateNode();

    protected:
        virtual bool onUpdate(Node *const target, const UpdateSignal &signal);
    };

}

#endif