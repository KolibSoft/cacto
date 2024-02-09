#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/Reference.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Window/Handler.hpp>
#include <Cacto/UI/Thickness.hpp>
#include <Cacto/UI/Inflatable.hpp>
#include <Cacto/UI/Box.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_UI_API Block
        : public Box,
          public virtual sf::Drawable,
          public virtual Inflatable,
          public virtual Handler,
          public virtual ChildNode
    {

    public:
        Block &&setLeft(f32t value, bool resize = false);
        Block &&setRight(f32t value, bool resize = false);
        Block &&setTop(f32t value, bool resize = false);
        Block &&setBottom(f32t value, bool resize = false);

        Block &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Block &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Block &&shrink(const Thickness &thickness);
        Block &&expand(const Thickness &thickness);

        Reference<Node> getBackground() const;
        Block &&setBackground(Reference<Node> value);

        const Thickness &getMargin() const;
        Block &&setMargin(const Thickness &value);

        const Thickness &getPadding() const;
        Block &&setPadding(const Thickness &value);

        f32t getMinWidth() const;
        Block &&setMinWidth(f32t value);

        f32t getMaxWidth() const;
        Block &&setMaxWidth(f32t value);

        f32t getMinHeight() const;
        Block &&setMinHeight(f32t value);

        f32t getMaxHeight() const;
        Block &&setMaxHeight(f32t value);

        Block &&setFixedWidth(f32t value);
        Block &&setFixedHeight(f32t value);

        Box getContainerBox() const;
        Box getContentBox() const;

        const sf::Transform &getVisualTransform() const;

        const std::string &getId() const override;
        Block &&setId(const std::string &value);

        Node *const getParent() const override;

        bool containsVisualPoint(const sf::Vector2f &point) const;

        void attach(ParentNode &parent) override;
        void detach() override;

        Block *clone() const override;
        Block *acquire() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool handle(const sf::Event &event) override;
        bool bubble(Node &target, const sf::Event &event) override;

        Block();
        virtual ~Block();

        Block(const Block &other);
        Block &operator=(const Block &other);

        Block(Block &&other);
        Block &operator=(Block &&other);

    protected:
        void clone(const Block &other);
        void acquire(Block &&other);

        void drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void handleBlock(const sf::Event &event);
        sf::Vector2f compactBlock(const sf::Vector2f &contentSize);
        sf::Vector2f inflateBlock(const sf::Vector2f &containerSize);
        void placeBlock(const sf::Vector2f &position);

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_id;
        Reference<Node> m_background;
        Thickness m_margin;
        Thickness m_padding;
        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;
        ParentNode *m_parent;

        mutable sf::Transform m_vTransform;
    };

    XmlValue CACTO_UI_API toXml(const Block &block);
    Block CACTO_UI_API toBlock(const XmlValue &xml);

    namespace block
    {

        class CACTO_UI_API XmlConverter
            : public virtual node::XmlConverter
        {
        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}
