#include <stdexcept>
#include <sstream>
#include <SFML/System/Time.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/TimeScanner.hpp>

namespace cacto
{

    Scanner &TimeScanner::getScanner() const
    {
        return *m_scanner;
    }

    void TimeScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool TimeScanner::scanMicroseconds(i64t &microseconds)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("us"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> microseconds;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanMilliseconds(i64t &milliseconds)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("ms"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> milliseconds;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanSeconds(i64t &seconds)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("s"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> seconds;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanMinutes(i64t &minutes)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("m"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> minutes;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanHours(i64t &hours)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("h"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> hours;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanDays(i64t &days)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->scanToken("d"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> days;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool TimeScanner::scanTime(sf::Time &time)
    {
        i64t MS = 1000;
        i64t S = 1000 * MS;
        i64t M = 60 * S;
        i64t H = 60 * M;
        i64t D = 24 * H;

        i64t days = 0;
        i64t hours = 0;
        i64t minutes = 0;
        i64t seconds = 0;
        i64t milliseconds = 0;
        i64t microseconds = 0;

        auto found = false;
        auto sign = true;

        if (scanDays(days))
        {
            if (days < 0)
            {
                sign = false;
                days = -days;
            }
            found = true;
        }

        if ((!found || found && m_scanner->dropBlank()) && scanHours(hours))
        {
            if (found)
            {
                if (hours < 0)
                    throw std::runtime_error("Min hours value is 0 when has days");
                if (hours > 24)
                    throw std::runtime_error("Max hours value is 23 when has days");
            }
            else if (hours < 0)
            {
                sign = false;
                hours = -hours;
            }
            found = true;
        }

        if ((!found || found && m_scanner->dropBlank()) && scanMinutes(minutes))
        {
            if (found)
            {
                if (minutes < 0)
                    throw std::runtime_error("Min minutes value is 0 when has hours");
                if (minutes > 59)
                    throw std::runtime_error("Max minutes value is 59 when has hours");
            }
            else if (minutes < 0)
            {
                sign = false;
                minutes = -minutes;
            }
            found = true;
        }

        if ((!found || found && m_scanner->dropBlank()) && scanSeconds(seconds))
        {
            if (found)
            {
                if (seconds < 0)
                    throw std::runtime_error("Min seconds value is 0 when has minutes");
                if (seconds > 59)
                    throw std::runtime_error("Max seconds value is 59 when has minutes");
            }
            else if (seconds < 0)
            {
                sign = false;
                seconds = -seconds;
            }
            found = true;
        }

        if ((!found || found && m_scanner->dropBlank()) && scanMilliseconds(milliseconds))
        {
            if (found)
            {
                if (milliseconds < 0)
                    throw std::runtime_error("Min milliseconds value is 0 when has seconds");
                if (milliseconds > 999)
                    throw std::runtime_error("Max milliseconds value is 999 when has seconds");
            }
            else if (milliseconds < 0)
            {
                sign = false;
                milliseconds = -milliseconds;
            }
            found = true;
        }

        if ((!found || found && m_scanner->dropBlank()) && scanMicroseconds(microseconds))
        {
            if (found)
            {
                if (microseconds < 0)
                    throw std::runtime_error("Min microseconds value is 0 when has milliseconds");
                if (microseconds > 999)
                    throw std::runtime_error("Max microseconds value is 999 when has milliseconds");
            }
            else if (microseconds < 0)
            {
                sign = false;
                microseconds = -microseconds;
            }
            found = true;
        }

        if (found)
        {
            auto us = days * D + hours * H + minutes * M + seconds * S + milliseconds * MS + microseconds;
            if (!sign)
                us = -us;
            time = sf::microseconds(us);
            return true;
        }
        return false;
    }

    TimeScanner::TimeScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    TimeScanner::~TimeScanner() = default;
}