#ifndef CACTO_ROW_LAYOUT_HPP
#define CACTO_ROW_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API RowLayout
        : public Block
    {

    public:
        void append(Node &child);
        void remove(Node &child);

        RowLayout();
        virtual ~RowLayout();

        RowLayout(const RowLayout &other);
        RowLayout &operator=(const RowLayout &other);

    protected:
        struct Holder;

        const Holder *const getHolder(const Node &node) const;
        const Holder *const getHolder(Node &&node) const = delete;

        Holder *const getHolder(const Node &node);
        Holder *const getHolder(Node &&node) = delete;
        
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        struct Holder
        {

        public:
            Holder() = default;
            virtual ~Holder() = default;

            Node *child;
            sf::Vector2f boxSize;
        };

    private:
        std::vector<Holder> m_holders;
    };

}

#endif