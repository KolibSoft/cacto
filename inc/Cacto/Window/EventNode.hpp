#ifndef CACTO_EVENT_NODE_HPP
#define CACTO_EVENT_NODE_HPP

#include <functional>
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
        using Listener = std::function<void(Node &target, const sf::Event &event)>;

        void dispatch(const sf::Event &event);
        void event(const sf::Event &event);
        void bubble(Node &target, const sf::Event &event);

        EventNode();
        virtual ~EventNode();

        static bool dispatch(Node &node, const sf::Event &event);
        static bool event(Node &node, const sf::Event &event);
        static bool bubble(Node &node, Node &target, const sf::Event &event);

    protected:
        virtual bool onDispatch(const sf::Event &event);
        virtual bool onEvent(const sf::Event &event);
        virtual bool onBubble(Node &target, const sf::Event &event);
    };

}

#endif