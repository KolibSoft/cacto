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
        sf::Vector2f compact();
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0});
        void place(const sf::Vector2f &position = {0, 0});

        InflatableNode();
        virtual ~InflatableNode();

        static sf::Vector2f compact(Node &node);
        static sf::Vector2f compactChildren(Node &node);

        static sf::Vector2f inflate(Node &node, const sf::Vector2f &containerSize = {0, 0});
        static sf::Vector2f inflateChildren(Node &node, const sf::Vector2f &containerSize = {0, 0});

        static void place(Node &node, const sf::Vector2f &position = {0, 0});
        static void placeChildren(Node &node, const sf::Vector2f &position = {0, 0});

    protected:
        virtual sf::Vector2f onCompact();
        virtual sf::Vector2f onInflate(const sf::Vector2f &containerSize);
        virtual void onPlace(const sf::Vector2f &position);
    };

}

#endif