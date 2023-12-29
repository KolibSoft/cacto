#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    namespace skeleton
    {

        enum Relation
        {
            Body,
            Bone
        };

        class CACTO_GRAPHICS_API Options
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

    }

    class CACTO_GRAPHICS_API Skeleton
        : public virtual sf::Drawable,
          public virtual ParentNode,
          public virtual ChildNode
    {

    public:
        using Relation = skeleton::Relation;
        using Options = skeleton::Options;

        const std::string &getId() const override;
        Skeleton &setId(const std::string &value);

        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable();

        ParentNode *const getParent() const override;

        szt getChildCount() const override;
        ChildNode *const getChild(szt index = 0) const override;

        const Options *const getOptions(const Node &child) const;
        Options *const getOptions(const Node &child);

        void attach(ParentNode &parent) override;
        void detach() override;

        void append(ChildNode &child) override;
        Skeleton &append(ChildNode &child, const Options &options);
        void remove(ChildNode &child) override;

        Skeleton();
        virtual ~Skeleton();

        Skeleton(const Skeleton &other) = delete;
        Skeleton &operator=(const Skeleton &other) = delete;

        Skeleton(Skeleton &&other) = delete;
        Skeleton &operator=(Skeleton &&other) = delete;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        struct holder;

        std::string m_id;
        sf::Transformable m_transformable;
        ParentNode *m_parent;
        std::vector<holder> m_holders;

        struct holder
        {
            ChildNode *child{};
            Options options{};
        };
    };

    std::string CACTO_GRAPHICS_API toString(Skeleton::Relation relation);
    void CACTO_GRAPHICS_API fromString(Skeleton::Relation &relation, const std::string &string);

    XmlValue CACTO_GRAPHICS_API toXml(const Skeleton &skeleton);
    void CACTO_GRAPHICS_API fromXml(Skeleton &skeleton, const XmlValue &xml);

    namespace skeleton
    {

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
