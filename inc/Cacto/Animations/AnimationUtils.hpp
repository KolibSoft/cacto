#pragma once

#include <string>
#include <Cacto/Animations/Export.hpp>

namespace cacto
{

    class Animation;

    std::string CACTO_ANIMATIONS_API getExpression(const Animation &animation);
    Animation CACTO_ANIMATIONS_API getBasicAnimation(const std::string &expression);

    std::string CACTO_ANIMATIONS_API getExpression(const Animation *animation);
    const Animation* CACTO_ANIMATIONS_API getAnimation(const std::string &expression);

}