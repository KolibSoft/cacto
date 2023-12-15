#include <Cacto/Lang/Printer.hpp>

namespace cacto
{

    std::ostream &Printer::getStream() const
    {
        return *m_stream;
    }

    void Printer::setStream(std::ostream &value)
    {
        m_stream = &value;
    }

    szt Printer::getPad() const
    {
        return m_pad;
    }

    void Printer::setPad(szt value)
    {
        m_pad = value;
    }

    szt Printer::getIdentation() const
    {
        return m_identation;
    }

    void Printer::setIdentation(szt value)
    {
        m_identation = value;
    }

    void Printer::print(c8t character)
    {
        m_line += character;
    }

    void Printer::print(const s8t &string)
    {
        m_line += string;
    }

    void Printer::print(const std::string &string)
    {
        m_line += string;
    }

    void Printer::println()
    {
        *m_stream << m_line << '\n';
        m_line = std::string(m_pad, ' ');
    }

    void Printer::flush()
    {
        *m_stream << m_line;
        m_line.clear();
    }

    void Printer::backspace(szt count)
    {
        m_line.resize(m_line.size() - count);
    }

    void Printer::backspaceln()
    {
        m_line.clear();
    }

    void Printer::ident(szt times, bool apply)
    {
        auto pad = m_pad + times * m_identation;
        m_pad = pad > 0 ? pad : 0;
        if (apply)
            m_line.insert(0, std::string(times * m_identation, ' '));
    }

    void Printer::dedent(szt times, bool apply)
    {
        auto pad = m_pad - times * m_identation;
        m_pad = pad > 0 ? pad : 0;
        if (apply)
            m_line.erase(m_line.begin(), m_line.begin() + times * m_identation);
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