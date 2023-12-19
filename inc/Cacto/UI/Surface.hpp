#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/UI/Box.hpp>
#include <Cacto/UI/UINode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class Geometry;

    class CACTO_UI_API Surface
        : public Box,
          public virtual LeafNode,
          public virtual UINode
    {

    public:
        const std::string &getId() const override;
        Surface &setId(const std::string &value);

        bool isInternal() const override;
        Surface &setInternal(bool value);

        Node *const getParent() const override;

        const Geometry &getGeometry() const;
        Surface &setGeometry(const Geometry &value);
        Surface &setGeometry(Geometry &&value) = delete;

        szt getPrecision() const;
        Surface &setPrecision(szt value);

        const sf::Color &getColor() const;
        Surface &setColor(const sf::Color &value);

        const sf::Texture *const getTexture() const;
        Surface &setTexture(const sf::Texture *const value, bool resetRect = true);

        const sf::FloatRect &getTextureRect() const;
        Surface &setTextureRect(const sf::FloatRect &value);

        void update(bool force = false) const;

        Surface(const Geometry &geometry = Rectangle::Identity, const sf::Color &color = sf::Color::White, const sf::Texture *texture = nullptr);
        Surface(Geometry &&geometry, const sf::Color &color = sf::Color::White, const sf::Texture *texture = nullptr) = delete;
        virtual ~Surface();

        Surface(const Surface &other);
        Surface &operator=(const Surface &other);

        Surface(Surface &&other);
        Surface &operator=(Surface &&other);

    protected:
        sf::VertexArray &getArray() const;
        void invalidate();

        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        virtual void onUpdate() const;
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        std::string m_id;
        bool m_internal;
        Node *m_parent;

        const Geometry *m_geometry;
        szt m_precision;
        sf::Color m_color;
        const sf::Texture *m_texture;
        sf::FloatRect m_textureRect;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    Surface CACTO_UI_API colorSurface(const sf::Color &color);
    Surface CACTO_UI_API textureSurface(const sf::Texture &texture, const sf::FloatRect &textureRect = {});

    XmlValue CACTO_UI_API toXml(const Surface &surface);
    void CACTO_UI_API fromXml(Surface &surface, const XmlValue &xml);

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
