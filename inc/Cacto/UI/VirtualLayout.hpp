#ifndef CACTO_VIRTUAL_LAYOUT_HPP
#define CACTO_VIRTUAL_LAYOUT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    class CACTO_UI_API VirtualLayout
        : public FrameLayout
    {

    public:
        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable();

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool event(const sf::Event &event) override;
        bool bubble(Node &target, const sf::Event &event) override;

        VirtualLayout();
        virtual ~VirtualLayout();

    private:
        sf::Transformable m_transformable;

        mutable Surface m_surface;
        mutable sf::RenderTexture m_texture;
    };

}

#endif