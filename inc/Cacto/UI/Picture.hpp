#ifndef CACTO_PICTURE_HPP
#define CACTO_PICTURE_HPP

#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/AnchorLayout.hpp>

namespace cacto
{

    class CACTO_UI_API Picture
        : public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        using Anchor = Box::Anchor;

        Node *const getParent() const override;

        const Block &getBlock() const;
        Block &getBlock();

        const Surface &getSurface() const;
        Surface &getSurface();

        Anchor getHorizontalAnchor() const;
        void setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        void setVerticalAnchor(Anchor value);

        Picture();
        virtual ~Picture();

        Picture(const Picture &other);
        Picture &operator=(const Picture &other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Node* m_parent;
        AnchorLayout m_frame;
        Surface m_surface;
    };

}

#endif