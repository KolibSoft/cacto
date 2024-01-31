#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Transform;
}

namespace cacto
{

    class Scanner;

    class CACTO_GRAPHICS_API TransformScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanTransform(f32t &a00, f32t &a01, f32t &a02, f32t &a10, f32t &a11, f32t &a12, f32t &a20, f32t &a21, f32t &a22);
        bool scanTransform(sf::Transform &transform);

        TransformScanner(Scanner &scanner);
        virtual ~TransformScanner();

    private:
        Scanner *m_scanner;
    };

}