#pragma once

#include <Cacto/Core/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

}

namespace cacto
{

    class Printer;

    class CACTO_CORE_API VectorPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printVector(f64t x, f64t y);
        void printVector(const sf::Vector2f &vector);

        VectorPrinter(Printer &printer);
        virtual ~VectorPrinter();

    private:
        Printer *m_printer;
    };

}