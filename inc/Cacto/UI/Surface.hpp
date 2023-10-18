#ifndef CACTO_SURFACE_HPP
#define CACTO_SURFACE_HPP

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

    class CACTO_UI_API Surface
        : public Box,
          public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        Node *const getParent() const override;

        Geometry &getGeometry() const;
        void setGeometry(Geometry &value);

        szt getPrecision() const;
        void setPrecision(szt value);

        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        const sf::Texture *const getTexture() const;
        void setTexture(const sf::Texture *const value);

        void update(bool force = false) const;

        Surface(Geometry &geometry, szt precision = 1, const sf::Color &color = sf::Color::White, sf::Texture *texture = nullptr);
        virtual ~Surface();

        Surface(const Surface& other);
        Surface& operator=(const Surface& other);

        static const Surface Rectangle;
        static const Surface Ellipse;

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        virtual void onUpdate() const;
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Node *m_parent;

        Geometry *m_geometry;
        szt m_precision;
        sf::Color m_color;
        const sf::Texture *m_texutre;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    Surface CACTO_UI_API colorSurface(const sf::Color &color, Geometry &geometry = Surface::Rectangle.getGeometry(), szt precision = 1);
    Surface CACTO_UI_API textureSurface(sf::Texture &texture, Geometry &geometry = Surface::Rectangle.getGeometry(), szt precision = 1);

}

#endif