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

    class Scanner;

    class CACTO_GRAPHICS_API RectScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanRect(f64t &left, f64t &top, f64t &width, f64t &height);
        bool scanRect(sf::FloatRect &rect);

        RectScanner(Scanner &scanner);
        virtual ~RectScanner();

    private:
        Scanner *m_scanner;
    };

}