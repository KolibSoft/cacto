#ifndef CACTO_SKELETON_HPP
#define CACTO_SKELETON_HPP

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

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
        : public sf::Transformable,
          public virtual DrawNode
    {

    public:
        using Relation = skeleton::Relation;
        using Options = skeleton::Options;

        const std::string &getTag() const override;
        void setTag(const std::string &value);

        Node *const getParent() const override;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        const Options *const getOptions(Node &child) const;
        Options *const getOptions(Node &child);

        Skeleton &append(Node &child, const Options &options = {}, bool internal = false);
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
        struct holder;

        std::string m_tag;
        Node *m_parent;
        std::vector<holder> m_holders;

        struct holder
        {
            Node *child{};
            Options options{};
            bool internal{};
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

#endif