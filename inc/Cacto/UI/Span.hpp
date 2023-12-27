#ifndef CACTO_SPAN_HPP
#define CACTO_SPAN_HPP

#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Graphics/TexDirection.hpp>
#include <Cacto/UI/UINode.hpp>

namespace sf
{
    class Font;
}

namespace cacto
{

    class CACTO_UI_API Span
        : public virtual ChildNode,
          public virtual UINode
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

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Span();
        virtual ~Span();

        Span(const Span &other) = delete;
        Span &operator=(const Span &other) = delete;

        Span(Span &&other) = delete;
        Span &operator=(Span &&other) = delete;

    private:
        std::string m_id;
        const sf::Font *m_font;
        sf::String m_string;
        Direction m_direction;
        u32t m_characterSize;
        sf::Color m_color;
        sf::Vector2f m_place;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

}

#endif