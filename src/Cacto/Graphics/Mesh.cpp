#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
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

    ParentNode *const Mesh::getParent() const
    {
        return m_parent;
    }

    void Mesh::attach(ParentNode &parent)
    {
        if (m_parent == &parent)
            return;
        if (m_parent != nullptr)
            throw std::runtime_error("This node is already attached to another parent");
        if (parent.hasAncestor(*this))
            throw std::runtime_error("This node is an ancestor");
        m_parent = &parent;
        parent.append(*this);
    }

    void Mesh::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    Mesh::Mesh()
        : m_id(),
          m_parent()
    {
    }

    Mesh::~Mesh()
    {
        detach();
    }

    XmlValue toXml(const Mesh &mesh)
    {
        auto xml = cacto::toXml((const sf::VertexArray &)mesh);
        xml.setName("Mesh");
        xml["id"] = mesh.getId();
        return std::move(xml);
    }

    void fromXml(Mesh &mesh, const XmlValue &xml)
    {
        cacto::fromXml((sf::VertexArray &)mesh, xml);
        mesh.setId(xml.getAttribute("id"));
    }

    namespace mesh
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Mesh *mesh = nullptr;
            if (value && typeid(*value) == typeid(Mesh) && (mesh = dynamic_cast<const Mesh *>(value)))
            {
                auto xml = cacto::toXml(*mesh);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Mesh")
            {
                auto mesh = std::make_shared<Mesh>();
                cacto::fromXml(*mesh, xml);
                Node::XmlStack.push(mesh);
                return mesh.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}