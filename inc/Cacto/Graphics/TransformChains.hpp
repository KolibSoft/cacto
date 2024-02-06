#pragma once

#include <Cacto/Core/Morph.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

    class Angle;
    class Transform;

}

namespace cacto
{

    class CACTO_GRAPHICS_API TransformChains
        : public virtual Morph
    {

    public:
        virtual sf::Transform &asTransform() = 0;

        TransformChains &translate(const sf::Vector2f &offset) &;
        inline TransformChains &&translate(const sf::Vector2f &offset) &&;

        TransformChains &scale(const sf::Vector2f &factors) &;
        inline TransformChains &&scale(const sf::Vector2f &factors) &&;

        TransformChains &rotate(const sf::Angle &angle) &;
        inline TransformChains &&rotate(const sf::Angle &angle) &&;

        TransformChains &combine(const sf::Transform &transform) &;
        inline TransformChains &&combine(const sf::Transform &transform) &&;

        TransformChains() = default;
        virtual ~TransformChains() = default;
    };

}

#include <Cacto/Graphics/TransformChains.inl>