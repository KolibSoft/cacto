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

    i32t Scanner::scanClass(const std::string &set)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && set.find(c) != std::string::npos)
            index += 1;
        m_cursor += index;
        return index;
    }

    i32t Scanner::scanToken(const std::string &set)
    {
        i32t index = 0;
        c8t c = 0;
        while ((c = available(index)) && index < set.size() && set[index] == c)
            index += 1;
        if (index != set.size())
            return 0;
        m_cursor += index;
        return index;
    }

    i32t Scanner::scanGroup(std::initializer_list<std::function<i32t()>> set)
    {
        i32t index = 0;
        for (auto &scan : set)
        {
            index = scan();
            if (index > 0)
                return index;
        }
        return index;
    }

    i32t Scanner::scanSequence(std::initializer_list<std::function<i32t()>> set)
    {
        i32t index = 0;
        for (auto &scan : set)
        {
            auto step = scan();
            if (step == 0)
            {
                m_cursor -= index;
                return 0;
            }
            if (step == -1)
                continue;
            index += step;
        }
        return index;
    }

    i32t Scanner::scanOption(std::function<i32t()> set)
    {
        auto index = set();
        if (index == 0)
            return -1;
        return index;
    }

    i32t Scanner::scanRange(i32t min, i32t max, std::function<i32t()> set)
    {
        auto index = set();
        if (index < min || index > max)
            return 0;
        return index;
    }

    i32t Scanner::scanNot(std::function<i32t()> set)
    {
        i32t index = 0;
        i32t step = 0;
        while ((step = set()) <= 0)
        {
            index += 1;
            m_cursor += 1;
        }
        m_cursor -= step;
        return index;
    }

    i32t Scanner::scanWhile(std::function<i32t()> set)
    {
        i32t index = 0;
        i32t step = 0;
        while (available(0) && (step = set()) > 0)
            index += step;
        return index;
    }

    i32t Scanner::scanBlank()
    {
        auto index = scanClass(" \t\n");
        return index;
    }

    i32t Scanner::scanDigit()
    {
        auto index = scanClass("0123456789");
        return index;
    }

    i32t Scanner::scanWord()
    {
        auto index = scanClass("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        return index;
    }

    i32t Scanner::scanIdentifier()
    {
        auto under = [&]
        {
            return scanToken("_");
        };
        auto word = [&]
        {
            return scanWord();
        };
        auto digit = [&]
        {
            return scanDigit();
        };
        auto index = scanSequence({[&]
                                   {
                                       return scanGroup({under, word});
                                   },
                                   [&]
                                   {
                                       return scanWhile([&]
                                                        { return scanGroup({under, word, digit}); });
                                   }});
        return index;
    }

    i32t Scanner::dropBlank()
    {
        auto index = scanBlank();
        drop();
        return index;
    }

    i32t Scanner::dropToken(const std::string &set)
    {
        auto index = scanToken(set);
        drop();
        return index;
    }

    Scanner::Scanner()
        : m_source(nullptr),
          m_start(0),
          m_cursor(0)
    {
    }

    Scanner::~Scanner() = default;

}