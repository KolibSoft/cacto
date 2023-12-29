#ifndef CACTO_SPAN_HPP
#define CACTO_SPAN_HPP

#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/TextDirection.hpp>
#include <Cacto/UI/Inflatable.hpp>

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
        using Direction = cacto::TextDirection;

        const std::string &getId() const override;
        Span &setId(const std::string &value);

        const sf::Font *const getFont() const;
        Span &setFont(const sf::Font *const value);

        const sf::String &getString() const;
        Span &setString(const sf::String &value);

        Direction getDirection() const;
        Span &setDirection(Direction value);

        u32t getCharacterSize() const;
        Span &setCharacterSize(u32t value);

        const sf::Color &getColor() const;
        Span &setColor(const sf::Color &value);

        ParentNode *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool containsVisualPoint(const sf::Vector2f &point) const;

        Span();
        virtual ~Span();

        Span(const Span &other) = delete;
        Span &operator=(const Span &other) = delete;

        Span(Span &&other) = delete;
        Span &operator=(Span &&other) = delete;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_id;
        const sf::Font *m_font;
        sf::String m_string;
        Direction m_direction;
        u32t m_characterSize;
        sf::Color m_color;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
        mutable sf::Transform m_vTransform;
    };

    XmlValue CACTO_UI_API toXml(const Span &span);
    void CACTO_UI_API fromXml(Span &span, const XmlValue &xml);

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

#endif