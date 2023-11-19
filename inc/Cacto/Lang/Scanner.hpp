#ifndef CACTO_SCANNER_HPP
#define CACTO_SCANNER_HPP

#include <limits>
#include <string>
#include <functional>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class CACTO_LANG_API Scanner
    {

    public:
        const std::string *getSource() const;
        void setSource(const std::string *value, i32t start = 0, i32t cursor = 0);

        i32t getStart() const;
        void setStart(i32t value);

        i32t getCursor() const;
        void setCursor(i32t value);

        c8t available(i32t index = 0) const;

        std::string take();
        void drop();

        i32t scanClass(const std::string &set, bool optional = false, szt min = 1, szt max = std::numeric_limits<szt>::max());
        i32t scanToken(const std::string &set, bool optional = false);
        i32t scanNotClass(const std::string &set);
        i32t discardClass(const std::string &set);

        i32t scanBlank();
        i32t scanDigit();
        i32t scanWord();

        i32t dropBlank();
        i32t dropToken(const std::string &set);

        Scanner();
        virtual ~Scanner();

    private:
        const std::string *m_source;
        i32t m_start;
        i32t m_cursor;
    };

}

#endif