#ifndef CACTO_LABEL_HPP
#define CACTO_LABEL_HPP

#include <Cacto/UI/Span.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Label
        : public Block
    {

    public:
        const Span &getSpan() const;
        Span &getSpan();

        Anchor getHorizontalAnchor() const;
        void setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        void setVerticalAnchor(Anchor value);

        Label(const sf::Font &font, const sf::String &string = "", u32t characterSize = 30);
        Label(sf::Font &&font, const sf::String &string = "", u32t characterSize = 30) = delete;

        virtual ~Label();

        Label(const Label &other);
        Label &operator=(const Label &other);

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Span m_span;
        Anchor m_hAnchor;
        Anchor m_vAnchor;
    };

}

#endif