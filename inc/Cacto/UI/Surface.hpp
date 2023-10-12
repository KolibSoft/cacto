#ifndef CACTO_SURFACE_HPP
#define CACTO_SURFACE_HPP

#include <memory>
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

    using SharedTexture = std::shared_ptr<sf::Texture>;
    using WeakNode = std::weak_ptr<Node>;

    class Geometry;
    using SharedGeometry = std::shared_ptr<Geometry>;

    class Surface;
    using SharedSurface = std::shared_ptr<Surface>;

    class CACTO_UI_API Surface
        : public std::enable_shared_from_this<Surface>,
          public Box,
          public virtual LeafNode,
          public virtual DrawNode,
          public virtual InflatableNode
    {

    public:
        SharedNode getParent() const override;

        const SharedGeometry &getGeometry() const;
        void setGeometry(const SharedGeometry &value);

        szt getPrecision() const;
        void setPrecision(szt value);

        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        const SharedTexture &getTexture() const;
        void setTexture(const SharedTexture &value);

        void update(bool force = false) const;

        Surface();
        virtual ~Surface();

    protected:
        void onAttach(const SharedNode &parent) override;
        void onDetach(const SharedNode &parent) override;

        virtual void onUpdate() const;
        bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        WeakNode m_parent;

        SharedGeometry m_geometry;
        szt m_precision;
        sf::Color m_color;
        SharedTexture m_texutre;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    SharedSurface CACTO_UI_API makeColorSurface(const sf::Color &color, const SharedGeometry &geometry = nullptr, szt precision = 1);
    SharedSurface CACTO_UI_API makeTextureSurface(const SharedTexture &texture, const SharedGeometry &geometry = nullptr, szt precision = 1);

}

#endif