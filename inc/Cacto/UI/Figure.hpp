#ifndef CACTO_FIGURE_HPP
#define CACTO_FIGURE_HPP

#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    class CACTO_UI_API Figure
        : public Surface
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

        Figure(const sf::Texture &texture, Scale scale = Fill);
        virtual ~Figure();

        Figure(const Figure &other);
        Figure &operator=(const Figure &other);

    protected:
        void onUpdate() const override;

    private:
        Scale m_scale;
        
        sf::Vector2f m_size;
    };

}

#endif