#pragma once

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
        virtual void update(const sf::Time &time);
        void updateChildren(const sf::Time &time) const;

        UpdateNode();
        virtual ~UpdateNode();

        static void update(Node &node, const sf::Time &time);
        static void updateChildren(const Node &node, const sf::Time &time);
    };

}