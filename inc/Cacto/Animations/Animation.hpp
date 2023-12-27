#pragma once

#include <SFML/System/Time.hpp>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/ResourceStack.hpp>
#include <Cacto/Animations/Export.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Animation
    {

    public:
        enum Direction
        {
            Forward,
            Reverse
        };

        enum Mode
        {
            Once,
            Repeat,
            Flip
        };

        const sf::Time &getDelay() const;
        void setDelay(const sf::Time &value);

        const sf::Time &getDuration() const;
        void setDuration(const sf::Time &value);

        Direction getDirection() const;
        void setDirection(Direction value);

        Mode getMode() const;
        void setMode(Mode value);

        f32t getRatio(const sf::Time &lifetime) const;
        szt getIndex(const sf::Time &lifetime, szt frameCount) const;

        Animation(const sf::Time &delay = sf::Time::Zero, const sf::Time &duration = sf::Time::Zero, Direction direction = Forward, Mode mode = Once);
        virtual ~Animation();

        static ResourceStack<Animation> XmlStack;

    private:
        sf::Time m_delay;
        sf::Time m_duration;
        Direction m_direction;
        Mode m_mode;
    };

    XmlValue CACTO_ANIMATIONS_API toXml(const Animation &animation);
    void CACTO_ANIMATIONS_API fromXml(Animation &animation, const XmlValue &xml);

    XmlValue CACTO_ANIMATIONS_API toXml(const Animation *const &animation);
    void CACTO_ANIMATIONS_API fromXml(Animation *&animation, const XmlValue &xml);

    template class CACTO_ANIMATIONS_API XmlConverter<Animation>;

    namespace animation
    {

        class CACTO_ANIMATIONS_API XmlConverter
            : public virtual cacto::XmlConverter<Animation>
        {
        public:
            XmlValue toXml(const Animation *const value) const override;
            Animation *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_ANIMATIONS_API Converter;

    }

}
