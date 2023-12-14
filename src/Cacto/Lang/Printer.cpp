#include <stdexcept>
#include <Cacto/Lang/Printer.hpp>

namespace cacto
{

    std::ostream &Printer::getStream() const
    {
        return *m_stream;
    }

    Printer &Printer::setStream(std::ostream &value)
    {
        m_stream = &value;
        return *this;
    }

    szt Printer::getPad() const
    {
        return m_pad;
    }

    Printer &Printer::setPad(szt value)
    {
        m_pad = value;
        return *this;
    }

    szt Printer::getIdentation() const
    {
        return m_identation;
    }

    Printer &Printer::setIdentation(szt value)
    {
        m_identation = value;
        return *this;
    }

    Printer &Printer::print(c8t character)
    {
        m_line += character;
        return *this;
    }

    Printer &Printer::print(const s8t &string)
    {
        m_line += string;
        return *this;
    }

    Printer &Printer::print(const std::string &string)
    {
        m_line += string;
        return *this;
    }

    Printer &Printer::println()
    {
        *m_stream << m_line << '\n';
        m_line.clear();
        return *this;
    }

    Printer &Printer::flush()
    {
        *m_stream << m_line;
        m_line.clear();
        return *this;
    }

    Printer &Printer::backspace(szt count)
    {
        m_line.resize(m_line.size() - count);
        return *this;
    }

    Printer &Printer::backspaceln()
    {
        m_line.clear();
        return *this;
    }

    Printer &Printer::ident(szt times)
    {
        auto pad = m_pad + times * m_identation;
        m_pad = pad > 0 ? pad : 0;
        return *this;
    }

    Printer &Printer::dedent(szt times)
    {
        auto pad = m_pad - times * m_identation;
        m_pad = pad > 0 ? pad : 0;
        return *this;
    }

    Printer::Printer(std::ostream &stream)
        : m_stream(&stream),
          m_line(),
          m_pad(),
          m_identation()
    {
    }

    Printer::~Printer() = default;

}