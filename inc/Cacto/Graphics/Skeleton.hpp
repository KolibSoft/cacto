#ifndef CACTO_SKELETON_HPP
#define CACTO_SKELETON_HPP

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

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

        const Holder *const getHolder(const Node &child) const;
        const Holder *const getHolder(Node &&child) const = delete;

        Holder *const getHolder(const Node &child);
        Holder *const getHolder(Node &&child) = delete;

        Holder &append(Node &child, bool internal = false);
        void remove(Node &child);

        Skeleton();
        virtual ~Skeleton();

        Skeleton(const Skeleton &other);
        Skeleton &operator=(const Skeleton &other);

        Skeleton(Skeleton &&other);
        Skeleton &operator=(Skeleton &&other);

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

    std::string CACTO_GRAPHICS_API toString(Skeleton::Relation relation);
    void CACTO_GRAPHICS_API fromString(Skeleton::Relation relation, const std::string &string);

    XmlValue CACTO_GRAPHICS_API toXml(const Skeleton &skeleton);
    void CACTO_GRAPHICS_API fromXml(Skeleton &skeleton, const XmlValue &xml);

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

            Holder(Node &node, bool internal);
            virtual ~Holder();

        private:
            sf::Vector2f m_coord;
            Skeleton::Relation m_relation;
        };

        class CACTO_GRAPHICS_API XmlConverter
            : public virtual node::XmlConverter
        {

        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_GRAPHICS_API Converter;

    }

}

#endif