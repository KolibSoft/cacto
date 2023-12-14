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
        Printer &setStream(std::ostream &value);

        szt getPad() const;
        Printer &setPad(szt value);

        szt getIdentation() const;
        Printer &setIdentation(szt value);

        Printer &print(c8t character);
        Printer &print(const s8t &string);
        Printer &print(const std::string &string);
        Printer &println();
        Printer &flush();

        Printer &backspace(szt count);
        Printer &backspaceln();

        Printer &ident(szt times);
        Printer &dedent(szt times);

        Printer(std::ostream &stream);
        virtual ~Printer();

    private:
        std::ostream *m_stream;
        std::string m_line;
        szt m_pad;
        szt m_identation;
    };

}
