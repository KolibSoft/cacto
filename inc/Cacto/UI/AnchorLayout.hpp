#ifndef CACTO_ANCHOR_LAYOUT_HPP
#define CACTO_ANCHOR_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Block.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API AnchorLayout
        : public Block
    {

    public:
        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        Anchor getHorizontalAnchor(const Node &child) const;
        Anchor getHorizontalAnchor(Node &&child) const = delete;

        void setHorizontalAnchor(Node &child, Anchor value);

        Anchor getVerticalAnchor(const Node &child) const;
        Anchor getVerticalAnchor(Node &&child) const = delete;

        void setVerticalAnchor(Node &child, Anchor value);

        void append(Node &child);
        void remove(Node &child);

        AnchorLayout();
        virtual ~AnchorLayout();

        AnchorLayout(const AnchorLayout &other);
        AnchorLayout &operator=(const AnchorLayout &other);

    protected:
        struct Holder;

        const Holder *const getHolder(const Node &node) const;
        const Holder *const getHolder(Node &&node) const = delete;

        Holder *const getHolder(const Node &node);
        Holder *const getHolder(Node &&node) = delete;

        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        struct Holder
        {

        public:
            Holder() = default;
            virtual ~Holder() = default;

            Node *child;
            Anchor hAnchor;
            Anchor vAnchor;
            sf::Vector2f boxSize;
        };

    private:
        std::vector<Holder> m_holders;
    };

}

#endif