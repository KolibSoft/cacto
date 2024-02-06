#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/TransformableChains.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public virtual sf::Drawable,
          public virtual TransformableChains,
          public virtual ChildNode
    {

    public:
        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable() override;

        const sf::VertexArray &asArray() const;
        sf::VertexArray &asArray();

        const sf::Texture *getTexture() const;
        Mesh &setTexture(const sf::Texture *value) &;
        inline Mesh &&setTexture(const sf::Texture *value) &&;

        const std::string &getId() const override;
        Mesh &setId(const std::string &value) &;
        inline Mesh &&setId(const std::string &value) &&;

        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        Mesh *clone() const override;
        Mesh *acquire() override;

        Mesh();
        virtual ~Mesh();

        Mesh(const Mesh &other);
        Mesh &operator=(const Mesh &other);

        Mesh(Mesh &&other);
        Mesh &operator=(Mesh &&other);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Transformable m_transformable;
        sf::VertexArray m_array;
        const sf::Texture *m_texture;
        std::string m_id;
        ParentNode *m_parent;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Mesh &mesh);
    Mesh CACTO_GRAPHICS_API toMesh(const XmlValue &xml);

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

#include <Cacto/Graphics/Mesh.inl>