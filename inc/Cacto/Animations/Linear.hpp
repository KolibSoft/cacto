#ifndef CACTO_LINEAR_HPP
#define CACTO_LINEAR_HPP

#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    template <typename T>
    class Linear
        : public Animation
    {

    public:
        const T &getFrom() const;
        void setFrom(const T &value);

        const T &getTo() const;
        void setTo(const T &value);

        T getValue(const sf::Time &lifetime) const;

        Linear();
        virtual ~Linear();

    private:
        T m_from;
        T m_to;
    };

}

#include <Cacto/Animations/Linear.inl>

#endif