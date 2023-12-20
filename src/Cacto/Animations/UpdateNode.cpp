#include <Cacto/Animations/UpdateNode.hpp>

namespace cacto
{

    void UpdateNode::update(const sf::Time &time)
    {
        auto object = dynamic_cast<Object *>(this);
        if (object)
            UpdateNode::update(object->as<Node>(), time);
    }

    UpdateNode::UpdateNode() = default;

    UpdateNode::~UpdateNode() = default;

    void UpdateNode::update(const Shared<Node> &node, const sf::Time &time)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto updateNode = std::dynamic_pointer_cast<UpdateNode>(node);
        if (updateNode)
            updateNode->onUpdate(time);
        else
            UpdateNode::updateChildren(node, time);
    }

    void UpdateNode::updateChildren(const Shared<Node> &node, const sf::Time &time)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            if (child)
                UpdateNode::update(child, time);
        }
    }

    void UpdateNode::updateChildren(const sf::Time &time)
    {
        auto object = dynamic_cast<Object *>(this);
        if (object)
            UpdateNode::updateChildren(object->as<Node>(), time);
    }

    void UpdateNode::onUpdate(const sf::Time &time)
    {
        updateChildren(time);
    }

}