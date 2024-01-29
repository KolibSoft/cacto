#pragma once

#include <string>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class CACTO_CORE_API Node
    {

    public:
        virtual const std::string &getId() const = 0;
        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Node *const getChild(szt index = 0) const = 0;
        i32t getChildIndex(const Node &child) const;

        template <typename T = Node>
        T *const firstDescendant(const std::string &id) const;

        template <typename T = Node>
        T *const firstAncestor(const std::string &id) const;

        bool hasDescendant(const Node &node) const;
        bool hasAncestor(const Node &node) const;

        Node() = default;
        virtual ~Node() = default;
    };

    template class CACTO_CORE_API XmlConverter<Node>;

}

#include <Cacto/Core/Node.inl>