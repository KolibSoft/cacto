#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/Utils.hpp>

namespace cacto
{

    Node *const Mesh::getParent() const
    {
        return m_parent;
    }

    Mesh::Mesh(sf::PrimitiveType primitive, szt count)
        : sf::VertexArray(primitive, count),
          m_parent(nullptr)
    {
    }

    Mesh::~Mesh() = default;

    Mesh::Mesh(const Mesh &other)
        : sf::VertexArray(other),
          m_parent(nullptr)
    {
    }

    Mesh &Mesh::operator=(const Mesh &other)
    {
        sf::VertexArray::operator=(other);
        return *this;
    }

    Mesh::Mesh(Mesh &&other)
        : sf::VertexArray(other),
          m_parent(nullptr)
    {
    }

    Mesh &Mesh::operator=(Mesh &&other)
    {
        sf::VertexArray::operator=(std::move(other));
        return *this;
    }

    void Mesh::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Mesh::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Mesh::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(*dynamic_cast<const sf::VertexArray *>(this), states);
    }

    XmlValue toXml(const Mesh &mesh)
    {
        XmlValue xml{"Mesh", {}};
        auto &attributes = xml.asAttributes();
        auto &content = xml.asContent();
        attributes["primitive"] = std::to_string(int(mesh.getPrimitiveType()));
        for (szt i = 0; i < mesh.getVertexCount(); i++)
        {
            auto &vertex = mesh[i];
            content.push_back(cacto::toXml(vertex));
        }
        return xml;
    }

    void fromXml(Mesh &mesh, const XmlValue &xml)
    {
        auto &attributes = xml.asAttributes();
        auto &content = xml.asContent();
        mesh.setPrimitiveType((sf::PrimitiveType)std::stoi(attributes.at("primitive")));
        mesh.clear();
        for (auto &vertex : content)
        {
            sf::Vertex _vertex{};
            cacto::fromXml(_vertex, vertex);
            mesh.append(_vertex);
        }
    }

    namespace mesh
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Mesh *mesh = nullptr;
            if (value && (mesh = dynamic_cast<const Mesh *>(value)))
            {
                auto xml = cacto::toXml(*mesh);
                return xml;
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getName() == "Mesh")
            {
                auto mesh = new Mesh();
                cacto::fromXml(*mesh, xml);
                return mesh;
            }
            return nullptr;
        }

    }

}