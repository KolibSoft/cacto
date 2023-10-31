#ifndef CACTO_BLOCK_HPP
#define CACTO_BLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/UI/Thickness.hpp>
#include <Cacto/UI/Box.hpp>
#include <Cacto/UI/InflatableNode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_UI_API Block
        : public Box,
          public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        Node *const getParent() const override;

        Node *const getBackground() const;
        void setBackground(Node *const value);

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        void setFixedWidth(f32t value);
        void setFixedHeight(f32t value);

        Box getContainerBox() const;
        Box getContentBox() const;

        Block();
        virtual ~Block();

        Block(const Block &other);
        Block &operator=(const Block &other);

    protected:
        sf::Vector2f compactContent(const sf::Vector2f &contentSize);
        
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Node *m_parent;
        Node *m_background;
        Thickness m_margin;
        Thickness m_padding;
        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;
    };

}

#endif