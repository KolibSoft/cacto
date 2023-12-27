#pragma once

#include <SFML/System/Vector2.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API InflatableNode
        : public virtual Node
    {

    public:
        virtual sf::Vector2f compact();
        sf::Vector2f compactChildren() const;

        virtual sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0});
        sf::Vector2f inflateChildren(const sf::Vector2f &containerSize) const;

        virtual void place(const sf::Vector2f &position = {0, 0});
        void placeChildren(const sf::Vector2f &position);

        InflatableNode();
        virtual ~InflatableNode();

        static sf::Vector2f compact(Node &node);
        static sf::Vector2f compactChildren(const Node &node);

        static sf::Vector2f inflate(Node &node, const sf::Vector2f &containerSize = {0, 0});
        static sf::Vector2f inflateChildren(const Node &node, const sf::Vector2f &containerSize = {0, 0});

        static void place(Node &node, const sf::Vector2f &position = {0, 0});
        static void placeChildren(const Node &node, const sf::Vector2f &position = {0, 0});
    };

}
