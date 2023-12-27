#ifndef CACTO_SPAN_HPP
#define CACTO_SPAN_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Cacto/UI/UINode.hpp>

namespace cacto
{

    class CACTO_UI_API Span
        : public virtual ChildNode,
          public virtual UINode
    {

    public:
        using Style = sf::Text::Style;

        const std::string &getId() const override;
        Span &setId(const std::string &value);

        const sf::Font *const getFont() const;
        Span &setFont(const sf::Font *const value);

        const sf::String &getString() const;
        Span &setString(const sf::String &value);

        const sf::Text &asText() const;
        sf::Text &asText();

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
        sf::Text m_text;
        sf::Vector2f m_place;
        ParentNode *m_parent;
    };

}

#endif