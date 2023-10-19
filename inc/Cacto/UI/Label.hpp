#ifndef CACTO_LABEL_HPP
#define CACTO_LABEL_HPP

#include <Cacto/UI/Span.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    class CACTO_UI_API Label
        : public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        using Anchor = Box::Anchor;

        Node *const getParent() const override;

        const Block &getBlock() const;
        Block &getBlock();

        const Span &getSpan() const;
        Span &getSpan();

        Anchor getHorizontalAnchor() const;
        void setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        void setVerticalAnchor(Anchor value);

        Label(const sf::Font &font, const sf::String &string = "", u32t characterSize = 30);
        Label(sf::Font &&font, const sf::String &string = "", u32t characterSize = 30) = delete;

        virtual ~Label();

        Label(const Label &other);
        Label &operator=(const Label &other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        FrameLayout m_frame;
        Span m_span;
    };

}

#endif