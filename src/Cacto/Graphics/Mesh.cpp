#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/Graphics/Mesh.hpp>

namespace cacto
{

    const sf::Transformable &Mesh::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &Mesh::asTransformable()
    {
        return m_transformable;
    }

    const sf::VertexArray &Mesh::asArray() const
    {
        return m_array;
    }

    sf::VertexArray &Mesh::asArray()
    {
        return m_array;
    }

    const std::string &Mesh::getId() const
    {
        return m_id;
    }

    Mesh &Mesh::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    Node *const Mesh::getParent() const
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

    XmlValue Mesh::toXml() const
    {
        XmlValue xml{"Mesh", {}};
        xml["id"] = getId();
        auto txml = cacto::toXml(m_transformable);
        auto axml = cacto::toXml(m_array);
        for (auto &pair : txml.asAttributes())
            xml[pair.first] = pair.second;
        for (auto &pair : axml.asAttributes())
            xml[pair.first] = pair.second;
        xml.asContent() = std::move(axml.asContent());
        return std::move(xml);
    }

    void Mesh::fromXml(const XmlValue &xml)
    {
        setId(xml.getAttribute("id"));
        m_transformable = toTransformable(xml);
        m_array = toVertexArray(xml);
    }

    Mesh::Mesh()
        : m_transformable(),
          m_array(),
          m_id(),
          m_parent()
    {
    }

    Mesh::~Mesh()
    {
        detach();
    }

    void Mesh::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto _states = states;
        _states.transform *= m_transformable.getTransform();
        target.draw(m_array, _states);
    }

    namespace mesh
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Mesh *mesh = nullptr;
            if (value && typeid(*value) == typeid(Mesh) && (mesh = dynamic_cast<const Mesh *>(value)))
            {
                auto xml = mesh->toXml();
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Mesh")
            {
                auto mesh = new Mesh();
                mesh->fromXml(xml);
                return mesh;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}