#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public virtual sf::Drawable,
          public virtual ChildNode
    {

    public:
        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable();

        const sf::VertexArray &asArray() const;
        sf::VertexArray &asArray();

        const std::string &getId() const override;
        Mesh &setId(const std::string &value);

        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        XmlValue toXml() const;
        void fromXml(const XmlValue &xml);

        Mesh();
        virtual ~Mesh();

        Mesh(const Mesh &other) = delete;
        Mesh &operator=(const Mesh &other) = delete;

        Mesh(Mesh &&other) = delete;
        Mesh &operator=(Mesh &&other) = delete;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Transformable m_transformable;
        sf::VertexArray m_array;
        std::string m_id;
        ParentNode *m_parent;
    };

    namespace mesh
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
