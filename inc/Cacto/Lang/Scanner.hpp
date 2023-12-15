#pragma once

#include <limits>
#include <string>
#include <istream>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class CACTO_LANG_API Scanner
    {

    public:
        std::istream &getStream() const;
        void setStream(std::istream &value);

        i32t getStart() const;
        void setStart(i32t value);

        i32t getCursor() const;
        void setCursor(i32t value);

        bool scanln();
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

        void dropBlankln();

        Scanner(std::istream &stream);
        virtual ~Scanner();

        static bool option(bool result);

    private:
        std::istream *m_stream;
        std::string m_line;
        i32t m_start;
        i32t m_cursor;
    };

}
