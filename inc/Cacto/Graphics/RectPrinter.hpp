#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    class Printer;

    class CACTO_GRAPHICS_API RectPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printRect(f64t left, f64t top, f64t width, f64t height);
        void printRect(const sf::FloatRect &rect);

        RectPrinter(Printer &printer);
        virtual ~RectPrinter();

    private:
        Printer *m_printer;
    };

}