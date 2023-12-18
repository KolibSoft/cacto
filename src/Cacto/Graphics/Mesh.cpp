#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Mesh.hpp>

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

    Mesh::~Mesh()
    {
        if (m_parent)
            Node::unlink(*m_parent, *this);
    }

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
        : sf::VertexArray(std::move(other)),
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
        auto &content = xml.asContent();
        xml["primitive"] = cacto::toString(mesh.getPrimitiveType());
        for (szt i = 0; i < mesh.getVertexCount(); i++)
        {
            auto &vertex = mesh[i];
            content.push_back(cacto::toXml(vertex));
        }
        return xml;
    }

    void fromXml(Mesh &mesh, const XmlValue &xml)
    {
        mesh = {};
        sf::PrimitiveType primitive;
        cacto::fromString(primitive, xml.getAttribute("primitive", "Points"));
        mesh.setPrimitiveType(primitive);
        auto source = xml.getAttribute("source");
        if (source.size() > 0)
        {
            JsonValue json = nullptr;
            json.fromFile(source);
            fromJson((sf::VertexArray &)mesh, json);
        }
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                sf::Vertex vertex{};
                cacto::fromXml(vertex, item);
                mesh.append(vertex);
            }
    }

    namespace mesh
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Mesh *mesh = nullptr;
            if (value && typeid(*value) == typeid(Mesh) && (mesh = dynamic_cast<const Mesh *>(value)))
            {
                auto xml = cacto::toXml(*mesh);
                return xml;
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Mesh")
            {
                auto mesh = new Mesh();
                cacto::fromXml(*mesh, xml);
                return mesh;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}