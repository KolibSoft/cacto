#include <stdexcept>
#include <Cacto/Lang/Printer.hpp>

namespace cacto
{

    std::string *const Printer::getTarget() const
    {
        return m_target;
    }

    void Printer::setTarget(std::string *const value, szt pad, szt identation)
    {
        m_target = value;
        m_pad = pad;
        m_identation = identation;
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

    void Printer::ident(szt times)
    {
        m_pad += times * m_identation;
    }

    void Printer::dedent(szt times)
    {
        m_pad -= times * m_identation;
    }

    void Printer::print(const std::string &value)
    {
        if (!m_target)
            throw std::runtime_error("Not target");
        *m_target += value;
    }

    void Printer::println()
    {
        if (!m_target)
            throw std::runtime_error("Not target");
        *m_target += '\n' + std::string(m_pad, ' ');
    }

    void Printer::backspace(szt times)
    {
        if (!m_target)
            throw std::runtime_error("Not target");
        if (times > m_target->size())
            times = m_target->size();
        for (szt i = 0; i < times; i++)
            m_target->pop_back();
    }

    void Printer::backspaceln(szt times)
    {
        if (!m_target)
            throw std::runtime_error("Not target");
        while (m_target->size() > 0 && m_target->back() != '\n')
            m_target->pop_back();
        if (m_target->size() > 0)
            m_target->pop_back();
    }

    Printer::Printer()
        : m_target(nullptr)
    {
    }

    Printer::~Printer() = default;

}