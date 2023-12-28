#pragma once

#include <SFML/Graphics/VertexArray.hpp>
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
        : public virtual ChildNode,
          public virtual UINode
    {

    public:
        const std::string &getId() const override;
        Surface &setId(const std::string &value);

        const Geometry *const getGeometry() const;
        Surface &setGeometry(const Geometry *const value);

        szt getPrecision() const;
        Surface &setPrecision(szt value);

        const sf::Color &getColor() const;
        Surface &setColor(const sf::Color &value);

        const sf::Texture *const getTexture() const;
        Surface &setTexture(const sf::Texture *const value, bool resetRect = true);

        const sf::FloatRect &getTextureRect() const;
        Surface &setTextureRect(const sf::FloatRect &value);

        const Box &asBox() const;
        Box &asBox();

        ParentNode *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Surface();
        virtual ~Surface();

        Surface(const Surface &other) = delete;
        Surface &operator=(const Surface &other) = delete;

        Surface(Surface &&other) = delete;
        Surface &operator=(Surface &&other) = delete;

    private:
        std::string m_id;
        Box m_box;
        const Geometry *m_geometry;
        szt m_precision;
        sf::Color m_color;
        const sf::Texture *m_texture;
        sf::FloatRect m_textureRect;
        ParentNode *m_parent;

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
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}
