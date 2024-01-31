#pragma once

#include <string>
#include <SFML/System/Time.hpp>
#include <Cacto/Lang/XmlConverter.hpp>
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

    private:
        sf::Time m_delay;
        sf::Time m_duration;
        Direction m_direction;
        Mode m_mode;
    };

    std::string CACTO_ANIMATIONS_API toString(Animation::Direction direction);
    Animation::Direction CACTO_ANIMATIONS_API toAnimationDirection(const std::string &string);

    std::string CACTO_ANIMATIONS_API toString(Animation::Mode mode);
    Animation::Mode CACTO_ANIMATIONS_API toAnimationMode(const std::string &string);

    XmlValue CACTO_ANIMATIONS_API toXml(const Animation &animation);
    Animation CACTO_ANIMATIONS_API toBasicAnimation(const XmlValue &xml);

    XmlValue CACTO_ANIMATIONS_API toXml(const Animation *const &animation);
    Animation *CACTO_ANIMATIONS_API toAnimation(const XmlValue &xml);

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
