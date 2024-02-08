#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public sf::Transformable,
          public virtual sf::Drawable,
          public virtual ChildNode
    {

    public:
        Mesh &&setOrigin(const sf::Vector2f &value);
        Mesh &&setPosition(const sf::Vector2f &value);
        Mesh &&setScale(const sf::Vector2f &value);
        Mesh &&setRotation(sf::Angle value);

        Mesh &&move(const sf::Vector2f &offset);
        Mesh &&scale(const sf::Vector2f &factors);
        Mesh &&rotate(const sf::Angle &angle);

        operator const sf::VertexArray &() const;
        operator sf::VertexArray &();

        sf::PrimitiveType getPrimitiveType() const;
        Mesh &&setPrimitiveType(sf::PrimitiveType value);

        szt getVertexCount() const;
        const sf::Vertex &operator[](szt index) const;
        sf::Vertex &operator[](szt index);
        Mesh &&append(const sf::Vertex &vertex);

        const sf::Texture *getTexture() const;
        Mesh &&setTexture(const sf::Texture *value);

        const std::string &getId() const override;
        Mesh &&setId(const std::string &value);

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
        void clone(const Mesh &other);
        void acquire(Mesh &&other);

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
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
