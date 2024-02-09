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

    Mesh &&Mesh::setOrigin(const sf::Vector2f &value)
    {
        sf::Transformable::setOrigin(value);
        return std::move(*this);
    }

    Mesh &&Mesh::setPosition(const sf::Vector2f &value)
    {
        sf::Transformable::setPosition(value);
        return std::move(*this);
    }

    Mesh &&Mesh::setScale(const sf::Vector2f &value)
    {
        sf::Transformable::setScale(value);
        return std::move(*this);
    }

    Mesh &&Mesh::setRotation(sf::Angle value)
    {
        sf::Transformable::setRotation(value);
        return std::move(*this);
    }

    Mesh &&Mesh::move(const sf::Vector2f &offset)
    {
        sf::Transformable::move(offset);
        return std::move(*this);
    }

    Mesh &&Mesh::scale(const sf::Vector2f &factors)
    {
        sf::Transformable::scale(factors);
        return std::move(*this);
    }

    Mesh &&Mesh::rotate(const sf::Angle &angle)
    {
        sf::Transformable::rotate(angle);
        return std::move(*this);
    }

    Mesh::operator const sf::VertexArray &() const
    {
        return m_array;
    }

    Mesh::operator sf::VertexArray &()
    {
        return m_array;
    }

    sf::PrimitiveType Mesh::getPrimitiveType() const
    {
        return m_array.getPrimitiveType();
    }

    Mesh &&Mesh::setPrimitiveType(sf::PrimitiveType value)
    {
        m_array.setPrimitiveType(value);
        return std::move(*this);
    }

    szt Mesh::getVertexCount() const
    {
        return m_array.getVertexCount();
    }

    const sf::Vertex &Mesh::operator[](szt index) const
    {
        return m_array[index];
    }

    sf::Vertex &Mesh::operator[](szt index)
    {
        return m_array[index];
    }

    Mesh &&Mesh::append(const sf::Vertex &vertex)
    {
        m_array.append(vertex);
        return std::move(*this);
    }

    const sf::Texture *Mesh::getTexture() const
    {
        return m_texture;
    }

    Mesh &&Mesh::setTexture(const sf::Texture *value)
    {
        m_texture = value;
        return std::move(*this);
    }

    const std::string &Mesh::getId() const
    {
        return m_id;
    }

    Mesh &&Mesh::setId(const std::string &value)
    {
        m_id = value;
        return std::move(*this);
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
        auto parent = m_parent;
        m_parent = nullptr;
        parent->remove(*this);
    }

    Mesh *Mesh::clone() const
    {
        auto mesh = new Mesh(*this);
        return mesh;
    }

    Mesh *Mesh::acquire()
    {
        auto mesh = new Mesh(std::move(*this));
        return mesh;
    }

    Mesh::Mesh()
        : sf::Transformable(),
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
        : Mesh()
    {
        *this = other;
    }

    Mesh &Mesh::operator=(const Mesh &other)
    {
        clone(other);
        return *this;
    }

    Mesh::Mesh(Mesh &&other)
        : Mesh()
    {
        *this = std::move(other);
    }

    Mesh &Mesh::operator=(Mesh &&other)
    {
        acquire(std::move(other));
        other.detach();
        return *this;
    }

    void Mesh::clone(const Mesh &other)
    {
        sf::Transformable::operator=(other);
        m_array = other.m_array;
        m_texture = other.m_texture;
        m_id = other.m_id;
    }

    void Mesh::acquire(Mesh &&other)
    {
        sf::Transformable::operator=(std::move(other));
        m_array = std::move(other.m_array);
        m_texture = other.m_texture;
        m_id = std::move(other.m_id);
        other.m_texture = nullptr;
    }

    void Mesh::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto _states = states;
        _states.texture = m_texture;
        _states.transform *= getTransform();
        target.draw(m_array, _states);
    }

    XmlValue toXml(const Mesh &mesh)
    {
        XmlValue xml{"Mesh", {}};
        xml |= toXml((const sf::Transformable &)mesh);
        xml |= toXml((const sf::VertexArray &)mesh);
        xml["texture"] = getExpression(mesh.getTexture());
        xml["id"] = mesh.getId();
        return std::move(xml);
    }

    Mesh toMesh(const XmlValue &xml)
    {
        Mesh mesh{};
        (sf::Transformable &)mesh = toTransformable(xml);
        (sf::VertexArray &)mesh = toVertexArray(xml);
        mesh.setTexture(getTexture(xml.getAttribute("texture")));
        mesh.setId(xml.getAttribute("id"));
        return std::move(mesh);
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
            if (xml.isTag() && xml.getName() == "Mesh")
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