#ifndef CACTO_LAYOUT_HPP
#define CACTO_LAYOUT_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/UI/Box.hpp>

namespace cacto
{

    namespace layout
    {

        class CACTO_UI_API Holder
            : public node::Holder
        {

        public:
            const Box &getBox() const;

            sf::Vector2f compact();
            sf::Vector2f inflate(const sf::Vector2f &containerSize);
            void place(const sf::Vector2f &place);

            Holder(Node &node);
            virtual ~Holder();

        private:
            Box m_box;
        };

    }

}

#endif