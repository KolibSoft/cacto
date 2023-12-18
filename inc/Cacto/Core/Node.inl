#include <Cacto/Core/Node.hpp>

namespace cacto
{

    namespace node
    {

        template <typename T>
        inline T *const Bag::getNodeAs(const std::string &tag) const
        {
            auto node = getNode(tag);
            return dynamic_cast<T *>(node);
        }

    }

}