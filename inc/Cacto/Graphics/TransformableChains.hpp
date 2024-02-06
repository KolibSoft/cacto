#pragma once

#include <Cacto/Core/Morph.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

    class Angle;
    class Transformable;

}

namespace cacto
{

    class CACTO_GRAPHICS_API TransformableChains
        : public virtual Morph
    {

    public:
        virtual sf::Transformable &asTransformable() = 0;

        TransformableChains &spawn(const sf::Vector2f &origin) &;
        inline TransformableChains &&spawn(const sf::Vector2f &origin) &&;

        TransformableChains &locate(const sf::Vector2f &position) &;
        inline TransformableChains &&locate(const sf::Vector2f &position) &&;

        TransformableChains &resize(const sf::Vector2f &factors) &;
        inline TransformableChains &&resize(const sf::Vector2f &factors) &&;

        TransformableChains &direction(const sf::Angle &angle) &;
        inline TransformableChains &&direction(const sf::Angle &angle) &&;

        TransformableChains &move(const sf::Vector2f &offset) &;
        inline TransformableChains &&move(const sf::Vector2f &offset) &&;

        TransformableChains &scale(const sf::Vector2f &factors) &;
        inline TransformableChains &&scale(const sf::Vector2f &factors) &&;

        TransformableChains &rotate(const sf::Angle &angle) &;
        inline TransformableChains &&rotate(const sf::Angle &angle) &&;

        TransformableChains() = default;
        virtual ~TransformableChains() = default;
    };

}

#include <Cacto/Graphics/TransformableChains.inl>