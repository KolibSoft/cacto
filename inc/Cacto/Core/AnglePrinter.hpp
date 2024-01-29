#pragma once

#include <Cacto/Core/Export.hpp>

namespace sf
{
    class Angle;
}

namespace cacto
{

    class Printer;
    class CACTO_CORE_API AnglePrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printDegrees(f64t degrees);
        void printRadians(f64t radians);
        void printAngle(const sf::Angle &angle);

        AnglePrinter(Printer &printer);
        virtual ~AnglePrinter();

    private:
        Printer *m_printer;
    };

}