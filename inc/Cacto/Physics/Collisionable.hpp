#ifndef CACTO_BODY_HPP
#define CACTO_BODY_HPP

namespace cacto
{

    class Collisionable
    {

    public:
        virtual void collision(Collisionable &other) = 0;

        Collisionable() = default;
        virtual ~Collisionable() = default;
    };

}

#endif