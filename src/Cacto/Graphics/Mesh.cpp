#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Pack.hpp>
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

    Mesh::Mesh()
        : m_id(),
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
        target.draw(*(dynamic_cast<const sf::VertexArray *>(this)), states);
    }

    XmlValue toXml(const Mesh &mesh)
    {
        auto xml = cacto::toXml((const sf::VertexArray &)mesh);
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