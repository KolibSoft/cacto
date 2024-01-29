#pragma once

#include <Cacto/Core/Export.hpp>

namespace sf
{
    class Angle;
}

namespace cacto
{

    class Scanner;

    class CACTO_CORE_API AngleScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanDegrees(f64t &degrees);
        bool scanRadians(f64t &radians);
        bool scanAngle(sf::Angle &angle);

        AngleScanner(Scanner &scanner);
        virtual ~AngleScanner();

    private:
        Scanner *m_scanner;
    };

}