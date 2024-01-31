#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/Graphics/TextureUtils.hpp>
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

    const sf::Texture *Mesh::getTexture() const
    {
        return m_texture;
    }

    Mesh &Mesh::setTexture(const sf::Texture *value)
    {
        m_texture = value;
        return *this;
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

    Mesh::Mesh()
        : m_transformable(),
          m_array(),
          m_texture(),
          m_id(),
          m_parent()
    {
    }

    Mesh::~Mesh()
    {
        detach();
    }

    Mesh::Mesh(const Mesh &other)
        : m_transformable(other.m_transformable),
          m_array(other.m_array),
          m_texture(other.m_texture),
          m_id(other.m_id),
          m_parent(nullptr)
    {
    }

    Mesh &Mesh::operator=(const Mesh &other)
    {
        Mesh copy{other};
        *this = std::move(copy);
        return *this;
    }

    Mesh::Mesh(Mesh &&other)
        : Mesh()
    {
        *this = std::move(other);
    }

    Mesh &Mesh::operator=(Mesh &&other)
    {
        m_transformable = std::move(other.m_transformable);
        m_array = std::move(other.m_array);
        m_texture = other.m_texture;
        m_id = std::move(other.m_id);
        other.detach();
        return *this;
    }

    void Mesh::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto _states = states;
        _states.texture = m_texture;
        _states.transform *= m_transformable.getTransform();
        target.draw(m_array, _states);
    }

    XmlValue toXml(const Mesh &mesh)
    {
        XmlValue xml{"Mesh", {}};
        xml["id"] = mesh.getId();
        xml["texture"] = getExpression(mesh.getTexture());
        auto txml = toXml(mesh.asTransformable());
        auto axml = toXml(mesh.asArray());
        for (auto &pair : txml.asAttributes())
            xml[pair.first] = pair.second;
        for (auto &pair : axml.asAttributes())
            xml[pair.first] = pair.second;
        xml.asContent() = std::move(axml.asContent());
        return std::move(xml);
    }

    Mesh toMesh(const XmlValue &xml)
    {
        Mesh mesh{};
        mesh.setId(xml.getAttribute("id"));
        mesh.setTexture(getTexture(xml.getAttribute("texture")));
        mesh.asTransformable() = toTransformable(xml);
        mesh.asArray() = toVertexArray(xml);
        return std::move(mesh);
    }

    namespace mesh
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Mesh *mesh = nullptr;
            if (value && typeid(*value) == typeid(Mesh) && (mesh = dynamic_cast<const Mesh *>(value)))
            {
                auto xml = cacto::toXml(mesh);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Mesh")
            {
                auto mesh = new Mesh();
                *mesh = toMesh(xml);
                return mesh;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}