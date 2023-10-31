#ifndef CACTO_SPAN_HPP
#define CACTO_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    class CACTO_UI_API Span
        : public sf::Text,
          public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        Node *const getParent() const override;

        using DrawNode::draw;

        Span(const sf::Font &font, const sf::String &string = "", u32t characterSize = 30);
        Span(sf::Font &&font, const sf::String &string = "", u32t characterSize = 30) = delete;

        virtual ~Span();

        Span(const Span &other);
        Span &operator=(const Span &other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Node *m_parent;
        sf::Vector2f m_place;
    };

}

#endif