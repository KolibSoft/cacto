#ifndef CACTO_UPDATE_NODE_HPP
#define CACTO_UPDATE_NODE_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/Animations/Export.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class UpdateSignal;

    class CACTO_ANIMATIONS_API UpdateNode
        : public virtual Node
    {

    public:
        bool handleSignal(Node &target, const Signal &signal);
        void update(const sf::Time &time);

        UpdateNode();
        virtual ~UpdateNode();

    protected:
        virtual bool onUpdate(Node &target, const UpdateSignal &signal);
    };

}

#endif