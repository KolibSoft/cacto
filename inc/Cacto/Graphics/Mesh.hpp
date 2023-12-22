#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const std::string &getId() const override;
        Mesh &setId(const std::string &value);

        Node *const getParent() const override;

        const sf::VertexArray &asArray() const;
        sf::VertexArray &asArray();

        Mesh();
        virtual ~Mesh();

        Mesh(const Mesh &other) = delete;
        Mesh &operator=(const Mesh &other) = delete;

        Mesh(Mesh &&other) = delete;
        Mesh &operator=(Mesh &&other) = delete;

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_id;
        sf::VertexArray m_array;
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
