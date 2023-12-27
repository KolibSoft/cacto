#pragma once

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
        virtual bool event(const sf::Event &event);
        bool eventChildren(const sf::Event &event) const;

        virtual bool bubble(Node &target, const sf::Event &event);
        bool bubbleParent(Node &target, const sf::Event &event) const;

        EventNode();
        virtual ~EventNode();

        static bool event(Node &node, const sf::Event &event);
        static bool eventChildren(const Node &node, const sf::Event &event);

        static bool bubble(Node &node, Node &target, const sf::Event &event);
        static bool bubbleParent(const Node &node, Node &target, const sf::Event &event);
    };

}
