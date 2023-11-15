#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    namespace layout
    {

        const Box &Holder::getBox() const
        {
            return m_box;
        }

        sf::Vector2f Holder::compact()
        {
            auto size = InflatableNode::compact(getNode());
            m_box.setWidth(size.x);
            m_box.setHeight(size.y);
            return size;
        }

        sf::Vector2f Holder::inflate(const sf::Vector2f &containerSize)
        {
            auto size = InflatableNode::inflate(getNode(), containerSize);
            m_box.setWidth(size.x);
            m_box.setHeight(size.y);
            return size;
        }

        void Holder::place(const sf::Vector2f &place)
        {
            InflatableNode::place(getNode(), place);
            m_box.setLeft(place.x);
            m_box.setTop(place.y);
        }

        Holder::Holder(Node &node)
            : node::Holder(node),
              m_box()
        {
        }

        Holder::~Holder() = default;

    }

}