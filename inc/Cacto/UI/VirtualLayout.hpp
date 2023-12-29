#pragma once

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

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool handle(const sf::Event &event) override;
        bool bubble(Node &target, const sf::Event &event) override;

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Transformable m_transformable;

        mutable Surface m_surface;
        mutable sf::RenderTexture m_texture;
    };

    XmlValue CACTO_UI_API toXml(const VirtualLayout &_virtual);
    void CACTO_UI_API fromXml(VirtualLayout &_virtual, const XmlValue &xml);

    namespace _virtual
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
