#ifndef CACTO_SPAN_HPP
#define CACTO_SPAN_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Cacto/Lang/Object.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/UI/UINode.hpp>

namespace cacto
{

    class CACTO_UI_API Span
        : public Object,
          public virtual LeafNode,
          public virtual UINode
    {

    public:
        using Style = sf::Text::Style;

        const std::string &getId() const override;
        Span &setId(const std::string &value);

        const Shared<const sf::Font> &getFont() const;
        Span &setFont(const Shared<const sf::Font> &value);

        const Shared<const sf::String> &getString() const;
        Span &setString(const Shared<const sf::String> &value);

        const sf::Text &asText() const;
        sf::Text &asText();

        Shared<Node> getParent() const override;

        Span();
        virtual ~Span();

    protected:
        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        std::string m_id;
        Shared<const sf::Font> m_font;
        Shared<const sf::String> m_string;
        sf::Text m_text;
        sf::Vector2f m_place;
        Weak<Node> m_parent;
    };

}

#endif