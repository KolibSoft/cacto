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

    class CACTO_ANIMATIONS_API UpdateNode
        : public virtual Node
    {

    public:
        void update(const sf::Time &time);

        UpdateNode();
        virtual ~UpdateNode();

        static void update(Node &node, const sf::Time &time);
        static void updateChildren(Node &node, const sf::Time &time);

    protected:
        void updateChildren(const sf::Time &time);

        virtual void onUpdate(const sf::Time &time);
    };

}

#endif