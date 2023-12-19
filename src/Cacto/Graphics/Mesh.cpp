#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Mesh.hpp>

namespace cacto
{

    const std::string &Mesh::getId() const
    {
        return m_id;
    }

    Mesh &Mesh::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    Shared<Node> Mesh::getParent() const
    {
        return m_parent.lock();
    }

    Mesh::Mesh(sf::PrimitiveType primitive, szt count)
        : sf::VertexArray(primitive, count),
          m_id(),
          m_parent()
    {
    }

    Mesh::~Mesh() = default;

    void Mesh::onAttach(const Shared<Node> &parent)
    {
        m_parent = parent;
    }

    void Mesh::onDetach(const Shared<Node> &parent)
    {
        m_parent.reset();
    }

    void Mesh::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(*dynamic_cast<const sf::VertexArray *>(this), states);
    }

    XmlValue toXml(const Mesh &mesh)
    {
        XmlValue xml{"Mesh", {}};
        auto &content = xml.asContent();
        xml["id"] = mesh.getId();
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
        mesh.setId(xml.getAttribute("id"));
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

        XmlValue XmlConverter::toXml(const Shared<const Node> &value) const
        {
            Shared<const Mesh> mesh = nullptr;
            auto ptr = value.get();
            if (value && typeid(*ptr) == typeid(Mesh) && (mesh = std::dynamic_pointer_cast<const Mesh>(value)))
            {
                auto xml = cacto::toXml(*mesh);
                return std::move(xml);
            }
            return nullptr;
        }

        Shared<Node> XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Mesh")
            {
                auto mesh = std::make_shared<Mesh>();
                cacto::fromXml(*mesh, xml);
                return std::move(mesh);
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}