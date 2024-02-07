#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/UI/Inflatable.hpp>
#include <Cacto/UI/Box.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class Geometry;

    class CACTO_UI_API Surface
        : public virtual sf::Drawable,
          public virtual Inflatable,
          public virtual ChildNode
    {

    public:
        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable();

        const sf::Vector2f &getOrigin() const;
        Surface &&setOrigin(const sf::Vector2f &value);

        const sf::Vector2f &getPosition() const;
        Surface &&setPosition(const sf::Vector2f &value);

        const sf::Vector2f &getScale() const;
        Surface &&setScale(const sf::Vector2f &value);

        sf::Angle getRotation() const;
        Surface &&setRotation(sf::Angle value);

        Surface &&move(const sf::Vector2f &offset);
        Surface &&scale(const sf::Vector2f &factors);
        Surface &&rotate(const sf::Angle &angle);

        const Box &asBox() const;
        Box &asBox();

        const Geometry *const getGeometry() const;
        Surface &&setGeometry(const Geometry *const value);

        szt getPrecision() const;
        Surface &&setPrecision(szt value);

        const sf::Color &getColor() const;
        Surface &&setColor(const sf::Color &value);

        const sf::Texture *const getTexture() const;
        Surface &&setTexture(const sf::Texture *const value, bool resetRect = true);

        const sf::FloatRect &getTextureRect() const;
        Surface &&setTextureRect(const sf::FloatRect &value);

        const sf::Transform &getVisualTransform() const;

        const std::string &getId() const override;
        Surface &&setId(const std::string &value);

        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        Surface *clone() const override;
        Surface *acquire() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool containsVisualPoint(const sf::Vector2f &point) const;

        Surface();
        virtual ~Surface();

        Surface(const Surface &other);
        Surface &operator=(const Surface &other);

        Surface(Surface &&other);
        Surface &operator=(Surface &&other);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Transformable m_transformable;
        Box m_box;
        const Geometry *m_geometry;
        szt m_precision;
        sf::Color m_color;
        const sf::Texture *m_texture;
        sf::FloatRect m_textureRect;
        std::string m_id;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
        mutable sf::Transform m_vTransform;
    };

    XmlValue CACTO_UI_API toXml(const Surface &surface);
    Surface CACTO_UI_API toSurface(const XmlValue &xml);

    namespace surface
    {

        class CACTO_UI_API XmlConverter
            : public virtual node::XmlConverter
        {

        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}
