#ifndef CACTO_PRINTER_HPP
#define CACTO_PRINTER_HPP

#include <string>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class CACTO_LANG_API Printer
    {

    public:
        std::string *const getTarget() const;
        void setTarget(std::string *const value, szt pad = 0, szt identation = 0);

        szt getPad() const;
        void setPad(szt value);

        szt getIdentation() const;
        void setIdentation(szt value);

        void ident(szt times = 1);
        void dedent(szt times = 1);

        void print(const std::string &value);
        void println();

        void backspace(szt times = 1);
        void backspaceln(szt times = 1);

        Printer();
        virtual ~Printer();

    private:
        std::string *m_target;
        szt m_pad;
        szt m_identation;
    };

}

#endif