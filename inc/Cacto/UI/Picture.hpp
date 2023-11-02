#ifndef CACTO_PICTURE_HPP
#define CACTO_PICTURE_HPP

#include <Cacto/UI/Figure.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Picture
        : public Block
    {

    public:
        const Figure &getFigure() const;
        Figure &getFigure();

        Picture(const sf::Texture &texture, Figure::Scale scale = Figure::Fill);
        Picture(sf::Texture &&texture, Figure::Scale scale = Figure::Fill) = delete;

        virtual ~Picture();

        Picture(const Picture &other);
        Picture &operator=(const Picture &other);

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Figure m_figure;
    };

}

#endif