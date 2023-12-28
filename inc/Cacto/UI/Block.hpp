#ifndef CACTO_BLOCK_HPP
#define CACTO_BLOCK_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/UI/Thickness.hpp>
#include <Cacto/UI/Box.hpp>
#include <Cacto/UI/UINode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_UI_API Block
        : public virtual ChildNode,
          public virtual UINode
    {

    public:
        const std::string &getId() const override;
        Block &setId(const std::string &value);

        Node *const getBackground() const;
        Block &setBackground(Node *const value);

        const Thickness &getMargin() const;
        Block &setMargin(const Thickness &value);

        const Thickness &getPadding() const;
        Block &setPadding(const Thickness &value);

        f32t getMinWidth() const;
        Block &setMinWidth(f32t value);

        f32t getMaxWidth() const;
        Block &setMaxWidth(f32t value);

        f32t getMinHeight() const;
        Block &setMinHeight(f32t value);

        f32t getMaxHeight() const;
        Block &setMaxHeight(f32t value);

        Block &setFixedWidth(f32t value);
        Block &setFixedHeight(f32t value);

        Box getContainerBox() const;
        Box getContentBox() const;

        const Box &asBox() const;
        Box &asBox();

        ParentNode *const getParent() const override;

        void drawBlock(sf::RenderTarget &target, const sf::RenderStates &states) const;
        void eventBlock(const sf::Event &event);
        sf::Vector2f compactBlock(const sf::Vector2f &contentSize);
        sf::Vector2f inflateBlock(const sf::Vector2f &containerSize);
        void placeBlock(const sf::Vector2f &position);

        void attach(ParentNode &parent) override;
        void detach() override;

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        bool event(const sf::Event &event) override;

        Block();
        virtual ~Block();

        Block(const Block &other) = delete;
        Block &operator=(const Block &other) = delete;

        Block(Block &&other) = delete;
        Block &operator=(Block &&other) = delete;

    private:
        std::string m_id;
        Box m_box;
        Node *m_background;
        Thickness m_margin;
        Thickness m_padding;
        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;
        ParentNode *m_parent;
    };

    XmlValue CACTO_UI_API toXml(const Block &block);
    void CACTO_UI_API fromXml(Block &block, const XmlValue &xml);

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

#endif