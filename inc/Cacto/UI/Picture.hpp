#pragma once

#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    enum class PictureScale
    {
        Fill,
        Fit,
        Crop
    };

    class CACTO_UI_API Picture
        : public Block
    {

    public:
        Picture &&setLeft(f32t value, bool resize = false);
        Picture &&setRight(f32t value, bool resize = false);
        Picture &&setTop(f32t value, bool resize = false);
        Picture &&setBottom(f32t value, bool resize = false);

        Picture &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Picture &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Picture &&shrink(const Thickness &thickness);
        Picture &&expand(const Thickness &thickness);

        Picture &&setBackground(Node *const value);
        Picture &&setBackground(Node &&value);

        Picture &&setMargin(const Thickness &value);
        Picture &&setPadding(const Thickness &value);

        Picture &&setMinWidth(f32t value);
        Picture &&setMaxWidth(f32t value);
        Picture &&setMinHeight(f32t value);
        Picture &&setMaxHeight(f32t value);

        Picture &&setFixedWidth(f32t value);
        Picture &&setFixedHeight(f32t value);

        operator const Surface &() const;
        operator Surface &();

        Picture &&setGeometry(const Geometry *const value);
        Picture &&setPrecision(szt value);
        Picture &&setColor(const sf::Color &value);
        Picture &&setTexture(const sf::Texture *const value, bool resetRect = true);

        PictureScale getScale() const;
        Picture &&setScale(PictureScale value);

        const sf::FloatRect &getTextureRect() const;
        Picture &&setTextureRect(const sf::FloatRect &value);

        BoxAnchor getHorizontalAnchor() const;
        Picture &&setHorizontalAnchor(BoxAnchor value);

        BoxAnchor getVerticalAnchor() const;
        Picture &&setVerticalAnchor(BoxAnchor value);

        Picture &&setId(const std::string &id);
        Picture *clone() const override;
        Picture *acquire() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Picture();
        virtual ~Picture();

        Picture(const Picture &other);
        Picture &operator=(const Picture &other);

        Picture(Picture &&other);
        Picture &operator=(Picture &&other);

    protected:
        void clone(const Picture &other);
        void acquire(Picture &&other);

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Surface m_surface;
        PictureScale m_scale;
        sf::FloatRect m_textureRect;
        BoxAnchor m_hAnchor;
        BoxAnchor m_vAnchor;
    };

    std::string CACTO_UI_API toString(PictureScale scale);
    PictureScale CACTO_UI_API toPictureScale(const std::string &string);

    XmlValue CACTO_UI_API toXml(const Picture &picture);
    Picture CACTO_UI_API toPicture(const XmlValue &xml);

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
