#include <stdexcept>
#include <Cacto/Lang/Scannable.hpp>
#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    std::istream &Scanner::getStream() const
    {
        return *m_stream;
    }

    void Scanner::setStream(std::istream &value)
    {
        m_stream = &value;
    }

    i32t Scanner::getStart() const
    {
        return m_start;
    }

    void Scanner::setStart(i32t value)
    {
        m_start = value;
    }

    i32t Scanner::getCursor() const
    {
        return m_cursor;
    }

    void Scanner::setCursor(i32t value)
    {
        m_cursor = value;
    }

    bool Scanner::scanln()
    {
        m_start = 0;
        m_cursor = 0;
        m_line.clear();
        auto success = (bool)std::getline(*m_stream, m_line);
        return success;
    }

    c8t Scanner::available(i32t index) const
    {
        auto at = m_start + m_cursor + index;
        if (at >= m_line.size())
            return 0;
        auto c = m_line.at(at);
        return c;
    }

    bool Scanner::scanln(Scannable &scannable)
    {
        auto success = scannable.scan(*this);
        return success;
    }

    std::string Scanner::take()
    {
        auto token = m_line.substr(m_start, m_cursor);
        m_start += m_cursor;
        m_cursor = 0;
        return token;
    }

    void Scanner::drop()
    {
        m_start += m_cursor;
        m_cursor = 0;
    }

    bool Scanner::scanClass(const std::string &set, bool optional, szt min, szt max)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && set.find(c) != std::string::npos)
            index += 1;
        if (index < min || index > max)
            return optional;
        m_cursor += index;
        return true;
    }

    bool Scanner::scanToken(const std::string &set, bool optional)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && index < set.size() && set[index] == c)
            index += 1;
        if (index != set.size())
            return optional;
        m_cursor += index;
        return true;
    }

    bool Scanner::scanNotClass(const std::string &set)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && set.find(c) == std::string::npos)
            index += 1;
        m_cursor += index;
        return index > 0;
    }

    bool Scanner::discardClass(const std::string &set)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && set.find(c) != std::string::npos)
            index -= 1;
        m_cursor += index;
        return index > 0;
    }

    bool Scanner::scanBlank()
    {
        auto result = scanClass(" \t\n");
        return result;
    }

    bool Scanner::scanDigit()
    {
        auto result = scanClass("0123456789");
        return result;
    }

    bool Scanner::scanWord()
    {
        auto result = scanClass("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        return result;
    }

    bool Scanner::dropBlank()
    {
        auto result = scanBlank();
        drop();
        return result;
    }

    bool Scanner::dropToken(const std::string &set)
    {
        auto result = scanToken(set);
        drop();
        return result;
    }

    void Scanner::dropBlankln()
    {
        while (dropBlank() || (m_start == m_line.size() && scanln()))
            ;
    }

    Scanner::Scanner(std::istream &stream)
        : m_stream(&stream),
          m_line(),
          m_start(),
          m_cursor()
    {
    }

    Scanner::~Scanner() = default;

    bool Scanner::option(bool result)
    {
        return true;
    }

}