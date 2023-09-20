#ifndef CACTO_EVENT_NODE_HPP
#define CACTO_EVENT_NODE_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API EventNode
        : public virtual Node
    {

    public:
        void event(const sf::Event &event);

        EventNode();
        virtual ~EventNode();

        static bool event(Node &node, const sf::Event &event);

    protected:
        virtual bool onEvent(const sf::Event &event);
    };

}

#endif