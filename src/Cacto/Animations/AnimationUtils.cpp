#include <Cacto/Animations/Animation.hpp>
#include <Cacto/Animations/AnimationPack.hpp>
#include <Cacto/Animations/AnimationUtils.hpp>

namespace cacto
{

    std::string getExpression(const Animation &animation)
    {
        auto id = getId(animation);
        if (id != "")
        {
            auto expression = "@animation/" + id;
            return std::move(expression);
        }
        return "";
    }

    Animation getBasicAnimation(const std::string &expression)
    {
        if (expression.compare(0, 11, "@animation/") == 0)
        {
            auto id = expression.substr(11);
            auto animation = getResource<Animation>(id);
            if (animation)
                return *animation;
        }
        return {};
    }

    std::string getExpression(const Animation *animation)
    {
        if (animation)
        {
            auto id = getId(*animation);
            if (id != "")
            {
                auto expression = "@animation/" + id;
                return std::move(expression);
            }
        }
        return "";
    }

    const Animation *getAnimation(const std::string &expression)
    {
        if (expression.compare(0, 11, "@animation/") == 0)
        {
            auto id = expression.substr(11);
            auto texture = getResource<Animation>(id);
            return texture;
        }
        return nullptr;
    }

}