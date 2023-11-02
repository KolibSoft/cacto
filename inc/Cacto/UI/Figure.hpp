#ifndef CACTO_FIGURE_HPP
#define CACTO_FIGURE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/UI/Box.hpp>
#include <Cacto/UI/InflatableNode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class Geometry;

    class CACTO_UI_API Figure
        : public Box,
          public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        Node *const getParent() const override;

        const sf::Texture &getTexture() const;
        void setTexture(const sf::Texture &value, bool resetRect = true);

        const sf::FloatRect &getTextureRect() const;
        void setTextureRect(const sf::FloatRect &value);

        void update(bool force = false) const;

        Figure(const sf::Texture &texture);
        virtual ~Figure();

        Figure(const Figure &other);
        Figure &operator=(const Figure &other);

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        virtual void onUpdate() const;
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Node *m_parent;

        const sf::Texture *m_texture;
        sf::FloatRect m_textureRect;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

}

#endif