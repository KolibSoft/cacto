#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Color;
}

namespace cacto
{

    class Scanner;

    class ColorScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanColor(u32t &color);
        bool scanColor(sf::Color &color);

        ColorScanner(Scanner &scanner);
        virtual ~ColorScanner();

    private:
        Scanner *m_scanner;
    };

}