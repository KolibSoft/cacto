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
        ScrollLayout();
        virtual ~ScrollLayout();

        ScrollLayout(const ScrollLayout &other);
        ScrollLayout &operator=(const ScrollLayout &other);

    protected:
        bool canScroll(f32t delta) const;

        bool onEvent(const sf::Event &event) override;

        void onScroll(const sf::Event &event) override;

    private:
        bool m_hovered;
        bool m_shift;
    };

}

#endif