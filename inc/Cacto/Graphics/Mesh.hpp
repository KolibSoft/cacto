#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/Object.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Mesh
        : public Object,
          public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const std::string &getId() const override;
        Mesh &setId(const std::string &value);

        Shared<const sf::VertexArray> getArray() const;
        Mesh& setArray(const Shared<const sf::VertexArray> &value);

        Shared<Node> getParent() const override;

        Mesh();
        virtual ~Mesh();

    protected:
        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_id;
        Shared<const sf::VertexArray> m_array;
        Weak<Node> m_parent;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Mesh &mesh);
    void CACTO_GRAPHICS_API fromXml(Mesh &mesh, const XmlValue &xml);

    namespace mesh
    {

        class CACTO_GRAPHICS_API XmlConverter
            : public virtual node::XmlConverter
        {
        public:
            XmlValue toXml(const Shared<const Node> &value) const override;
            Shared<Node> fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_GRAPHICS_API Converter;

    }

}
