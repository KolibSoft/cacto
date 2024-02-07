#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/TextDirection.hpp>
#include <Cacto/UI/Inflatable.hpp>
#include <Cacto/UI/Box.hpp>

namespace sf
{
    class Font;
}

namespace cacto
{

    class CACTO_UI_API Span
        : public Box,
          public virtual sf::Drawable,
          public virtual Inflatable,
          public virtual ChildNode
    {

    public:
        Span &&setLeft(f32t value, bool resize = false);
        Span &&setRight(f32t value, bool resize = false);
        Span &&setTop(f32t value, bool resize = false);
        Span &&setBottom(f32t value, bool resize = false);

        Span &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Span &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Span &&shrink(const Thickness &thickness);
        Span &&expand(const Thickness &thickness);

        const sf::Font *const getFont() const;
        Span &&setFont(const sf::Font *const value);

        const sf::String &getString() const;
        Span &&setString(const sf::String &value);

        TextDirection getDirection() const;
        Span &&setDirection(TextDirection value);

        u32t getCharacterSize() const;
        Span &&setCharacterSize(u32t value);

        const sf::Color &getColor() const;
        Span &&setColor(const sf::Color &value);

        const sf::Transform &getVisualTransform() const;

        const std::string &getId() const override;
        Span &&setId(const std::string &value);
        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        Span *clone() const override;
        Span *acquire() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool containsVisualPoint(const sf::Vector2f &point) const;

        Span();
        virtual ~Span();

        Span(const Span &other);
        Span &operator=(const Span &other);

        Span(Span &&other);
        Span &operator=(Span &&other);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const sf::Font *m_font;
        sf::String m_string;
        TextDirection m_direction;
        u32t m_characterSize;
        sf::Color m_color;
        std::string m_id;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
        mutable sf::Transform m_vTransform;
    };

    XmlValue CACTO_UI_API toXml(const Span &span);
    Span CACTO_UI_API toSpan(const XmlValue &xml);

    namespace span
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
