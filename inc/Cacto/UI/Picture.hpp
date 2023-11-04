#ifndef CACTO_PICTURE_HPP
#define CACTO_PICTURE_HPP

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
        void setScale(Scale value);

        const sf::FloatRect& getTextureRect() const;
        void setTextureRect(const sf::FloatRect& value);

        Anchor getHorizontalAnchor() const;
        void setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        void setVerticalAnchor(Anchor value);

        const Surface &getSurface() const;
        Surface &getSurface();

        Picture(const sf::Texture &texture, Scale scale = Fill);
        Picture(sf::Texture &&texture, Scale scale = Fill) = delete;

        virtual ~Picture();

        Picture(const Picture &other);
        Picture &operator=(const Picture &other);

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Surface m_surface;
        Scale m_scale;
        sf::FloatRect m_textureRect;
        Anchor m_hAnchor;
        Anchor m_vAnchor;
    };

}

#endif