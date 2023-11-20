#include <stdexcept>
#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    const std::string *Scanner::getSource() const
    {
        return m_source;
    }

    void Scanner::setSource(const std::string *value, i32t start, i32t cursor)
    {
        m_source = value;
        m_start = start;
        m_cursor = cursor;
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

    c8t Scanner::available(i32t index) const
    {
        if (m_source == nullptr)
            return 0;
        auto at = m_start + m_cursor + index;
        if (at >= m_source->size())
            return 0;
        auto c = m_source->at(at);
        return c;
    }

    std::string Scanner::take()
    {
        if (!m_source)
            throw std::runtime_error("Not source");
        auto token = m_source->substr(m_start, m_cursor);
        m_start += m_cursor;
        m_cursor = 0;
        return token;
    }

    void Scanner::drop()
    {
        if (!m_source)
            throw std::runtime_error("Not source");
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

    Scanner::Scanner()
        : m_source(nullptr),
          m_start(0),
          m_cursor(0)
    {
    }

    Scanner::~Scanner() = default;

    bool Scanner::option(bool result)
    {
        return true;
    }

}