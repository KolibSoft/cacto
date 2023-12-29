#ifndef CACTO_SCROLL_LAYOUT_HPP
#define CACTO_SCROLL_LAYOUT_HPP

#include <Cacto/Window/Scrollable.hpp>
#include <Cacto/UI/VirtualLayout.hpp>

namespace cacto
{

    class CACTO_UI_API ScrollLayout
        : public VirtualLayout,
          public virtual Scrollable
    {

    public:
        bool handle(const sf::Event &event) override;
        
        void scroll(sf::Mouse::Wheel wheel = sf::Mouse::Wheel::VerticalWheel, f32t delta = 0, i32t x = 0, i32t y = 0) override;

        ScrollLayout();
        virtual ~ScrollLayout();

    protected:
        bool canScroll(f32t delta) const;
        virtual void onScroll(const sf::Event &event);

    private:
        bool m_hovered;
        bool m_shift;
    };

}

#endif