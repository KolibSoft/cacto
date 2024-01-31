#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Transform;
}

namespace cacto
{

    class Printer;

    class CACTO_GRAPHICS_API TransformPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printTransform(f32t a00, f32t a01, f32t a02, f32t a10, f32t a11, f32t a12, f32t a20, f32t a21, f32t a22);
        void printTransform(const sf::Transform &transform);

        TransformPrinter(Printer &printer);
        virtual ~TransformPrinter();

    private:
        Printer *m_printer;
    };

}