#pragma once

#include <SFML/System/Time.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
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

    template class CACTO_ANIMATIONS_API JsonConverter<Animation>;

    std::string CACTO_ANIMATIONS_API toString(const Animation::Direction &direction);
    void CACTO_ANIMATIONS_API fromString(Animation::Direction &direction, const std::string &string);

    std::string CACTO_ANIMATIONS_API toString(const Animation::Mode &mode);
    void CACTO_ANIMATIONS_API fromString(Animation::Mode &mode, const std::string &string);

    JsonValue CACTO_ANIMATIONS_API toJson(const Animation &animation);
    void CACTO_ANIMATIONS_API fromJson(Animation &animation, const JsonValue &json);

    JsonValue CACTO_ANIMATIONS_API toJson(const Animation *const &animation);
    void CACTO_ANIMATIONS_API fromJson(Animation *&animation, const JsonValue &json);

    namespace animation
    {

        class CACTO_ANIMATIONS_API JsonConverter
            : public virtual cacto::JsonConverter<Animation>
        {
        public:
            JsonValue toJson(const Animation *const value) const override;
            Animation *fromJson(const JsonValue &json) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

        extern JsonConverter CACTO_ANIMATIONS_API Converter;

    }

}
