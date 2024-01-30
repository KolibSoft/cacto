#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/TransformableChains.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Skeleton
        : public virtual sf::Drawable,
          public virtual TransformableChains,
          public virtual ParentNode,
          public virtual ChildNode
    {

    public:
        enum Relation
        {
            Body,
            Bone
        };

        class Options;

        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable() override;

        const std::string &getId() const override;
        Skeleton &setId(const std::string &value);

        Node *const getParent() const override;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        const Options *const getOptions(const Node &child) const;
        Options *const getOptions(const Node &child);

        void attach(ParentNode &parent) override;
        void detach() override;

        void append(ChildNode &child) override;
        void remove(ChildNode &child) override;

        Skeleton &append(ChildNode &child, const Options &options);
        Skeleton &append(const std::shared_ptr<ChildNode> &child, const Options &options);

        XmlValue toXml() const;
        void fromXml(const XmlValue &xml);

        Skeleton();
        virtual ~Skeleton();

        Skeleton(const Skeleton &other) = delete;
        Skeleton &operator=(const Skeleton &other) = delete;

        Skeleton(Skeleton &&other) = delete;
        Skeleton &operator=(Skeleton &&other) = delete;

        class Options
        {

        public:
            const sf::Vector2f &getCoords() const;
            Options &setCoords(const sf::Vector2f &value);

            Relation getRelation() const;
            Options &setRelation(Relation value);

            Options(const sf::Vector2f &coords = {}, Relation relation = Body);
            virtual ~Options();

        private:
            sf::Vector2f m_coords;
            Relation m_relation;
        };

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        struct holder;

        sf::Transformable m_transformable;
        std::vector<std::shared_ptr<Node>> m_bag;
        std::string m_id;
        std::vector<holder> m_holders;
        ParentNode *m_parent;

        struct holder
        {
            ChildNode *child{};
            Options options{};
        };
    };

    std::string CACTO_GRAPHICS_API toString(Skeleton::Relation relation);
    Skeleton::Relation CACTO_GRAPHICS_API toRelation(const std::string &string);

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
