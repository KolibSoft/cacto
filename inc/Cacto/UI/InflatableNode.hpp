#ifndef CACTO_INFLATABLE_NODE_HPP
#define CACTO_INFLATABLE_NODE_HPP

#include <SFML/System/Vector2.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API InflatableNode
        : public virtual Node
    {

    public:
        sf::Vector2f compact(const sf::Vector2f &contentSize = {0, 0});
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0});
        void place(const sf::Vector2f &position = {0, 0});

        InflatableNode();
        virtual ~InflatableNode();

        static sf::Vector2f compact(Node &node, const sf::Vector2f &contentSize);
        static sf::Vector2f inflate(Node &node, const sf::Vector2f &containerSize);
        static void place(Node &node, const sf::Vector2f &position);

    protected:
        virtual sf::Vector2f onCompact(const sf::Vector2f &contentSize) = 0;
        virtual sf::Vector2f onInflate(const sf::Vector2f &containerSize) = 0;
        virtual void onPlace(const sf::Vector2f &position) = 0;
    };

}

#endif