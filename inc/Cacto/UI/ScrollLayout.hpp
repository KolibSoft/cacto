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

    XmlValue CACTO_UI_API toXml(const ScrollLayout &scroll);
    void CACTO_UI_API fromXml(ScrollLayout &scroll, const XmlValue &xml);

    namespace scroll
    {

        class CACTO_UI_API XmlConverter
            : public virtual node::XmlConverter
        {
        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}

#endif