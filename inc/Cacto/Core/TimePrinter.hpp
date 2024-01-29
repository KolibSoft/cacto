#pragma once

#include <Cacto/Core/Export.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class Printer;

    class CACTO_CORE_API TimePrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printMicroseconds(i64t microseconds);
        void printMilliseconds(i64t milliseconds);
        void printSeconds(i64t seconds);
        void printMinutes(i64t minutes);
        void printHours(i64t hours);
        void printDays(i64t days);
        void printTime(const sf::Time& time);

        TimePrinter(Printer &printer);
        virtual ~TimePrinter();

    private:
        Printer *m_printer;
    };

}