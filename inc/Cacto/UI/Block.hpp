#ifndef CACTO_BLOCK_HPP
#define CACTO_BLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/UI/Thickness.hpp>
#include <Cacto/UI/Box.hpp>
#include <Cacto/UI/UINode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_UI_API Block
        : public Box,
          public virtual LeafNode,
          public virtual UINode
    {

    public:
        Node *const getParent() const override;

        Node *const getBackground() const;
        Block& setBackground(Node *const value);

        const Thickness &getMargin() const;
        Block& setMargin(const Thickness &value);

        const Thickness &getPadding() const;
        Block& setPadding(const Thickness &value);

        f32t getMinWidth() const;
        Block& setMinWidth(f32t value);

        f32t getMaxWidth() const;
        Block& setMaxWidth(f32t value);

        f32t getMinHeight() const;
        Block& setMinHeight(f32t value);

        f32t getMaxHeight() const;
        Block& setMaxHeight(f32t value);

        Block& setFixedWidth(f32t value);
        Block& setFixedHeight(f32t value);

        Box getContainerBox() const;
        Box getContentBox() const;

        Block();
        virtual ~Block();

        Block(const Block &other);
        Block &operator=(const Block &other);

    protected:
        void drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void eventBlock(const sf::Event &event);
        sf::Vector2f compactBlock(const sf::Vector2f &contentSize);
        sf::Vector2f inflateBlock(const sf::Vector2f &containerSize);
        void placeBlock(const sf::Vector2f &position);

        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        bool onEvent(const sf::Event &event) override;

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