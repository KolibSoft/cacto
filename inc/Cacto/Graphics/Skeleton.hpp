#ifndef CACTO_SKELETON_HPP
#define CACTO_SKELETON_HPP

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    namespace skeleton
    {
        class Holder;
    }

    class CACTO_GRAPHICS_API Skeleton
        : public sf::Transformable,
          public virtual DrawNode
    {

    public:
        using Holder = skeleton::Holder;

        enum Relation
        {
            Body,
            Bone
        };

        Node *const getParent() const override;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        const sf::Vector2f &getCoord(Node &child) const;
        void setCoord(Node &child, const sf::Vector2f &value);

        Relation getRelation(Node &child) const;
        void setRelation(Node &child, Relation value);

        Holder &append(Node &child);
        void remove(Node &child);

        Skeleton();
        virtual ~Skeleton();

        Skeleton(const Skeleton &other);
        Skeleton &operator=(const Skeleton &other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Node *m_parent;
        std::vector<Holder> m_holders;
    };

    namespace skeleton
    {

        class CACTO_GRAPHICS_API Holder
            : public node::Holder
        {

        public:
            const sf::Vector2f &getCoord() const;
            Holder &setCoord(const sf::Vector2f &value);

            Skeleton::Relation getRelation() const;
            Holder &setRelation(Skeleton::Relation value);

            Holder(Node &node);
            virtual ~Holder();

        private:
            sf::Vector2f m_coord;
            Skeleton::Relation m_relation;
        };

    }

}

#endif