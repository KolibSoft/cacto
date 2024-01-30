#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Color;
}

namespace cacto
{

    class Printer;

    class CACTO_GRAPHICS_API ColorPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printColor(u32t color);
        void printColor(const sf::Color &color);

        ColorPrinter(Printer &printer);
        virtual ~ColorPrinter();

    private:
        Printer *m_printer;
    };

}