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

    using EventListener = std::function<void(const Shared<Node> &target, const sf::Event &event)>;

    class CACTO_WINDOW_API EventNode
        : public virtual Node
    {

    public:
        bool event(const sf::Event &event);
        bool bubble(const Shared<Node> &target, const sf::Event &event);

        EventNode();
        virtual ~EventNode();

        static bool event(const Shared<Node> &node, const sf::Event &event);
        static bool eventChildren(const Shared<Node> &node, const sf::Event &event);

        static bool bubble(const Shared<Node> &node, const Shared<Node> &target, const sf::Event &event);
        static bool bubbleParent(const Shared<Node> &node, const Shared<Node> &target, const sf::Event &event);

    protected:
        bool eventChildren(const sf::Event &event);
        bool bubbleParent(const Shared<Node> &target, const sf::Event &event);

        virtual bool onEvent(const sf::Event &event);
        virtual bool onBubble(const Shared<Node> &target, const sf::Event &event);
    };

}
