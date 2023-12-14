#pragma once

#include <limits>
#include <string>
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

        bool scanClass(const std::string &set, bool optional = false, szt min = 1, szt max = std::numeric_limits<szt>::max());
        bool scanToken(const std::string &set, bool optional = false);
        bool scanNotClass(const std::string &set);
        bool discardClass(const std::string &set);

        bool scanBlank();
        bool scanDigit();
        bool scanWord();

        bool dropBlank();
        bool dropToken(const std::string &set);

        Scanner();
        virtual ~Scanner();

        static bool option(bool result);

    private:
        const std::string *m_source;
        i32t m_start;
        i32t m_cursor;
    };

}
