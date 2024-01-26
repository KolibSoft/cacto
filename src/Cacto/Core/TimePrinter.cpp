#include <sstream>
#include <SFML/System/Time.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Core/TimePrinter.hpp>

namespace cacto
{

    Printer &TimePrinter::getPrinter() const
    {
        return *m_printer;
    }

    void TimePrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void TimePrinter::printMicroseconds(i64t microseconds)
    {
        std::stringstream stream{};
        stream << microseconds;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("us");
    }

    void TimePrinter::printMilliseconds(i64t milliseconds)
    {
        std::stringstream stream{};
        stream << milliseconds;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("ms");
    }

    void TimePrinter::printSeconds(i64t seconds)
    {
        std::stringstream stream{};
        stream << seconds;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("s");
    }

    void TimePrinter::printMinutes(i64t minutes)
    {
        std::stringstream stream{};
        stream << minutes;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("m");
    }

    void TimePrinter::printHours(i64t hours)
    {
        std::stringstream stream{};
        stream << hours;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("h");
    }

    void TimePrinter::printDays(i64t days)
    {
        std::stringstream stream{};
        stream << days;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("d");
    }

    void TimePrinter::printTime(const sf::Time &time)
    {
        i64t US = 1;
        i64t MS = 1000 * US;
        i64t S = 1000 * MS;
        i64t M = 60 * S;
        i64t H = 60 * M;
        i64t D = 24 * H;

        i64t us = time.asMicroseconds();
        if (us == 0)
        {
            m_printer->print("0");
        }
        else
        {
            auto sign = us >= 0;
            if (!sign)
            {
                m_printer->print("-");
                us = -us;
            }

            if (us >= D)
            {
                i64t d = us / D;
                if (d > 0)
                {
                    printDays(d);
                    m_printer->print(" ");
                }
                us %= D;
            }

            if (us >= H)
            {
                i64t h = us / H;
                if (h > 0)
                {
                    printHours(h);
                    m_printer->print(" ");
                }
                us %= H;
            }

            if (us >= M)
            {
                i64t m = us / M;
                if (m > 0)
                {
                    printMinutes(m);
                    m_printer->print(" ");
                }
                us %= M;
            }

            if (us >= S)
            {
                i64t s = us / S;
                if (s > 0)
                {
                    printSeconds(s);
                    m_printer->print(" ");
                }
                us %= S;
            }

            if (us >= MS)
            {
                i64t ms = us / MS;
                if (ms > 0)
                {
                    printMilliseconds(ms);
                    m_printer->print(" ");
                }
                us %= MS;
            }

            if (us > 0)
            {
                printMicroseconds(us);
                m_printer->print(" ");
            }

            m_printer->backspace();
        }
    }

    TimePrinter::TimePrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    TimePrinter::~TimePrinter() = default;

}