#ifndef CACTO_VIRTUAL_LAYOUT_HPP
#define CACTO_VIRTUAL_LAYOUT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    class CACTO_UI_API VirtualLayout
        : public FrameLayout,
          public EventNode
    {

    public:
        VirtualLayout();
        virtual ~VirtualLayout();

        VirtualLayout(const VirtualLayout &other);
        VirtualLayout &operator=(const VirtualLayout &other);

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        bool onEvent(const sf::Event &event) override;
        bool onBubble(Node &target, const sf::Event &event) override;

    private:
        mutable Surface m_surface;
        mutable sf::RenderTexture m_texture;
    };

}

#endif