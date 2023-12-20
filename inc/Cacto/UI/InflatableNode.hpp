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
        sf::Vector2f compact();
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0});
        void place(const sf::Vector2f &position = {0, 0});

        InflatableNode();
        virtual ~InflatableNode();

        static sf::Vector2f compact(Node &node);
        static sf::Vector2f compactChildren(const Node &node);

        static sf::Vector2f inflate(Node &node, const sf::Vector2f &containerSize = {0, 0});
        static sf::Vector2f inflateChildren(const Node &node, const sf::Vector2f &containerSize = {0, 0});

        static void place(Node &node, const sf::Vector2f &position = {0, 0});
        static void placeChildren(const Node &node, const sf::Vector2f &position = {0, 0});

    protected:
        sf::Vector2f compactChildren() const;
        sf::Vector2f inflateChildren(const sf::Vector2f &containerSize) const;
        void placeChildren(const sf::Vector2f &position);

        virtual sf::Vector2f onCompact();
        virtual sf::Vector2f onInflate(const sf::Vector2f &containerSize);
        virtual void onPlace(const sf::Vector2f &position);
    };

}
