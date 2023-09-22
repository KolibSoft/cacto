#ifndef CACTO_BODY_HPP
#define CACTO_BODY_HPP

#include <Cacto/Collisions/Trace.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class CACTO_COLLISIONS_API Body
    {

    public:
        virtual Trace getTrace() const = 0;
        virtual void collision(Body &other) = 0;

        Body();
        virtual ~Body();
    };

}

#endif