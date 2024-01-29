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

    class Scanner;

    class CACTO_CORE_API VectorScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanVector(f64t &x, f64t &y);
        bool scanVector(sf::Vector2f &vector);

        VectorScanner(Scanner &scanner);
        virtual ~VectorScanner();

    private:
        Scanner *m_scanner;
    };

}