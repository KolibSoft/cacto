#ifndef CACTO_LAYOUT_HPP
#define CACTO_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Layout
        : public Block
    {

    public:
        void append(Node &child);
        void remove(Node &child);

        Layout();
        virtual ~Layout();

        Layout(const Layout &other);
        Layout &operator=(const Layout &other);

    protected:
        class Holder;

        Holder *const getHolder(szt index = 0);
        const Holder *const getHolder(szt index = 0) const;

        Holder *const getHolder(const Node &child);
        Holder *const getHolder(Node &&child) = delete;

        const Holder *const getHolder(const Node &child) const;
        const Holder *const getHolder(Node &&child) const = delete;

        virtual Holder *onHold(Node &child);

        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        class Holder
        {

        public:
            const Node &getChild() const;
            Node &getChild();

            Holder(Node &child);
            virtual ~Holder();

        private:
            Node *m_child;
        };

    private:
        std::vector<Holder *> m_holders;
    };

}

#endif