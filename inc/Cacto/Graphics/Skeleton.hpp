#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Core/Reference.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    enum class SkeletonRelation
    {
        Body,
        Bone
    };

    class CACTO_GRAPHICS_API SkeletonOptions
    {

    public:
        const sf::Vector2f &getCoords() const;
        SkeletonOptions &setCoords(const sf::Vector2f &value);

        SkeletonRelation getRelation() const;
        SkeletonOptions &setRelation(SkeletonRelation value);

        SkeletonOptions(const sf::Vector2f &coords = {}, SkeletonRelation relation = SkeletonRelation::Body);
        virtual ~SkeletonOptions();

    private:
        sf::Vector2f m_coords;
        SkeletonRelation m_relation;
    };

    class CACTO_GRAPHICS_API Skeleton
        : public sf::Transformable,
          public virtual sf::Drawable,
          public virtual ParentNode,
          public virtual ChildNode
    {

    public:
        Skeleton &&setOrigin(const sf::Vector2f &value);
        Skeleton &&setPosition(const sf::Vector2f &value);
        Skeleton &&setScale(const sf::Vector2f &value);
        Skeleton &&setRotation(sf::Angle value);

        Skeleton &&move(const sf::Vector2f &offset);
        Skeleton &&scale(const sf::Vector2f &factors);
        Skeleton &&rotate(const sf::Angle &angle);

        const std::string &getId() const override;
        Skeleton &&setId(const std::string &value);

        Node *const getParent() const override;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        const SkeletonOptions *const getOptions(const Node &child) const;
        SkeletonOptions *const getOptions(const Node &child);

        void attach(ParentNode &parent) override;
        void detach() override;

        void append(ChildNode &child) override;
        Skeleton &&append(Reference<ChildNode> child, const SkeletonOptions &options);

        void remove(ChildNode &child) override;

        Skeleton *clone() const override;
        Skeleton *acquire() override;

        Skeleton();
        virtual ~Skeleton();

        Skeleton(const Skeleton &other);
        Skeleton &operator=(const Skeleton &other);

        Skeleton(Skeleton &&other);
        Skeleton &operator=(Skeleton &&other);

    protected:
        void clone(const Skeleton &other);
        void acquire(Skeleton &&other);

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        struct holder;

        std::string m_id;
        std::vector<holder> m_holders;
        ParentNode *m_parent;

        struct holder
        {
            Reference<ChildNode> child{};
            SkeletonOptions options{};
        };
    };

    std::string CACTO_GRAPHICS_API toString(SkeletonRelation relation);
    SkeletonRelation CACTO_GRAPHICS_API toRelation(const std::string &string);

    XmlValue CACTO_GRAPHICS_API toXml(const Skeleton &skeleton);
    Skeleton CACTO_GRAPHICS_API toSkeleton(const XmlValue &xml);

    namespace skeleton
    {

        class CACTO_GRAPHICS_API XmlConverter
            : public virtual cacto::XmlConverter<Node>
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
