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

        const Shared<const Geometry> &getGeometry() const;
        Surface &setGeometry(const Shared<const Geometry> &value);

        szt getPrecision() const;
        Surface &setPrecision(szt value);

        const sf::Color &getColor() const;
        Surface &setColor(const sf::Color &value);

        const Shared<const sf::Texture> &getTexture() const;
        Surface &setTexture(const Shared<const sf::Texture> &value, bool resetRect = true);

        const sf::FloatRect &getTextureRect() const;
        Surface &setTextureRect(const sf::FloatRect &value);

        Shared<Node> getParent() const override;

        void update(bool force = false) const;

        Surface();
        virtual ~Surface();

    protected:
        sf::VertexArray &getArray() const;
        void invalidate();

        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;

        virtual void onUpdate() const;
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        std::string m_id;
        Shared<const Geometry> m_geometry;
        szt m_precision;
        sf::Color m_color;
        Shared<const sf::Texture> m_texture;
        sf::FloatRect m_textureRect;
        Weak<Node> m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_UI_API toXml(const Surface &surface);
    void CACTO_UI_API fromXml(Surface &surface, const XmlValue &xml);

    namespace surface
    {

        class CACTO_UI_API XmlConverter
            : public virtual node::XmlConverter
        {

        public:
            XmlValue toXml(const Shared<const Node> &value) const override;
            Shared<Node> fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}
