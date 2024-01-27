#pragma once

#include <Cacto/Core/Export.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class Scanner;

    class CACTO_CORE_API TimeScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanMicroseconds(i64t &microseconds);
        bool scanMilliseconds(i64t &milliseconds);
        bool scanSeconds(i64t &seconds);
        bool scanMinutes(i64t &minutes);
        bool scanHours(i64t &hours);
        bool scanDays(i64t &days);
        bool scanTime(sf::Time &time);

        TimeScanner(Scanner &scanner);
        virtual ~TimeScanner();

    private:
        Scanner *m_scanner;
    };

}