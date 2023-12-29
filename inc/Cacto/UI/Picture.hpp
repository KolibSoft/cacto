#pragma once

#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Picture
        : public Block
    {

    public:
        enum Scale
        {
            Fill,
            Fit,
            Crop
        };

        Scale getScale() const;
        Picture &setScale(Scale value);

        const sf::FloatRect &getTextureRect() const;
        Picture &setTextureRect(const sf::FloatRect &value);

        Anchor getHorizontalAnchor() const;
        Picture &setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        Picture &setVerticalAnchor(Anchor value);

        const Surface &asSurface() const;
        Surface &asSurface();

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Picture();
        virtual ~Picture();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Surface m_surface;
        Scale m_scale;
        sf::FloatRect m_textureRect;
        Anchor m_hAnchor;
        Anchor m_vAnchor;
    };

    XmlValue CACTO_UI_API toXml(const Picture &picture);
    void CACTO_UI_API fromXml(Picture &picture, const XmlValue &xml);

    namespace picture
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
