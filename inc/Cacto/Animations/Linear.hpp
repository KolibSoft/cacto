#pragma once

#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Linear
        : public Animation
    {

    public:
        const f32t &getFrom() const;
        void setFrom(const f32t &value);

        const f32t &getTo() const;
        void setTo(const f32t &value);

        f32t getValue(const sf::Time &lifetime) const;

        Linear(f32t from = 0, f32t to = 0, const sf::Time &delay = sf::Time::Zero, const sf::Time &duration = sf::Time::Zero, Direction direction = Forward, Mode mode = Once);
        virtual ~Linear();

    private:
        f32t m_from;
        f32t m_to;
    };

    XmlValue CACTO_ANIMATIONS_API toXml(const Linear &linear);
    void CACTO_ANIMATIONS_API fromXml(Linear &linear, const XmlValue &xml);

    namespace linear
    {

        class CACTO_ANIMATIONS_API XmlConverter
            : public virtual animation::XmlConverter
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
