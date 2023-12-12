#ifndef CACTO_MESH_HPP
#define CACTO_MESH_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public sf::VertexArray,
          public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const std::string &getTag() const override;
        void setTag(const std::string &value);

        Node *const getParent() const override;

        Mesh(sf::PrimitiveType primitive = sf::PrimitiveType::Points, szt count = 0);
        virtual ~Mesh();

        Mesh(const Mesh &other);
        Mesh &operator=(const Mesh &other);

        Mesh(Mesh &&other);
        Mesh &operator=(Mesh &&other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_tag;
        Node *m_parent;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Mesh &mesh);
    void CACTO_GRAPHICS_API fromXml(Mesh &mesh, const XmlValue &xml);

    namespace mesh
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