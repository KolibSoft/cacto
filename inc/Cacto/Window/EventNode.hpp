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
    
    using EventListener = std::function<void(Node &target, const sf::Event &event)>;

    class CACTO_WINDOW_API EventNode
        : public virtual Node
    {

    public:
        bool event(const sf::Event &event);
        bool bubble(Node &target, const sf::Event &event);

        EventNode();
        virtual ~EventNode();

        static bool event(Node &node, const sf::Event &event);
        static bool eventChildren(Node &node, const sf::Event &event);

        static bool bubble(Node &node, Node &target, const sf::Event &event);
        static bool bubbleParent(Node &node, Node &target, const sf::Event &event);

    protected:
        bool eventChildren(const sf::Event &event);
        bool bubbleParent(Node &target, const sf::Event &event);

        virtual bool onEvent(const sf::Event &event);
        virtual bool onBubble(Node &target, const sf::Event &event);
    };

}

#endif