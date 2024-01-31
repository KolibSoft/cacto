#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/GeometryUtils.hpp>

namespace cacto
{

    std::string getExpression(const Geometry *geometry)
    {
        if (geometry)
        {
            auto id = getId(*geometry);
            if (id != "")
            {
                auto expression = "@geometry/" + id;
                return std::move(expression);
            }
        }
        return "";
    }

    const Geometry *getGeometry(const std::string &expression)
    {
        if (expression.compare(0, 10, "@geometry/") == 0)
        {
            auto id = expression.substr(10);
            auto texture = getResource<Geometry>(id);
            return texture;
        }
        return nullptr;
    }

}