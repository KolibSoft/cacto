#pragma once

#include <string>
#include <ostream>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class CACTO_LANG_API Printer
    {

    public:
        std::ostream &getStream() const;
        void setStream(std::ostream &value);

        szt getPad() const;
        void setPad(szt value);

        szt getIdentation() const;
        void setIdentation(szt value);

        void print(c8t character);
        void print(const s8t &string);
        void print(const std::string &string);
        void println();
        void flush();

        void backspace(szt count = 1);
        void backspaceln();

        void ident(szt times = 1);
        void dedent(szt times = 1);

        Printer(std::ostream &stream);
        virtual ~Printer();

    private:
        std::ostream *m_stream;
        std::string m_line;
        szt m_pad;
        szt m_identation;
    };

}
