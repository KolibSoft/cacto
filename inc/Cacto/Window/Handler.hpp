#pragma once

namespace sf
{
    class Event;
}

namespace cacto
{

    class Node;

    class Handler
    {

    public:
        virtual bool handle(const sf::Event &event) = 0;
        virtual bool bubble(Node &target, const sf::Event &event) = 0;

        Handler() = default;
        virtual ~Handler() = default;
    };

}