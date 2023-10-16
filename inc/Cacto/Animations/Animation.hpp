#ifndef CACTO_ANIMATION_HPP
#define CACTO_ANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Config.hpp>

namespace cacto
{

    template <typename T>
    class Animation
    {

    public:
        const T &getFrom() const;
        void setFrom(const T &value);

        const T &getTo() const;
        void setTo(const T &value);

        const sf::Time &getDelay() const;
        void setDelay(const sf::Time &value);

        const sf::Time &getDuration() const;
        void setDuration(const sf::Time &value);

        T getValue(const sf::Time &time) const;

        Animation();
        virtual ~Animation();

    private:
        T m_from;
        T m_to;
        sf::Time m_delay;
        sf::Time m_duration;
    };

    ///////////////////////////////////////////////////////////////////////

    template <>
    class Animation<sf::Color>
    {

    public:
        const sf::Color &getFrom() const;
        void setFrom(const sf::Color &value);

        const sf::Color &getTo() const;
        void setTo(const sf::Color &value);

        const sf::Time &getDelay() const;
        void setDelay(const sf::Time &value);

        const sf::Time &getDuration() const;
        void setDuration(const sf::Time &value);

        sf::Color getValue(const sf::Time &time) const;

        Animation();
        virtual ~Animation();

    private:
        sf::Color m_from;
        sf::Color m_to;
        sf::Time m_delay;
        sf::Time m_duration;
    };

}

#include <Cacto/Animations/Animation.inl>

#endif