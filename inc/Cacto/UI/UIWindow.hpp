#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/UI/Inflatable.hpp>
#include <Cacto/Window/Handler.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API UIWindow
        : public sf::RenderWindow,
          public virtual Inflatable,
          public virtual Handler,
          public virtual ParentNode
    {

    public:
        const std::string &getId() const override;
        UIWindow &setId(const std::string &value);

        szt getChildCount() const override;
        ChildNode *const getChild(szt index = 0) const override;

        void showContent();

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;
        void inflateContent();

        bool handle(const sf::Event &event) override;
        bool bubble(Node &target, const sf::Event &event) override;
        void handleContent();

        void append(ChildNode &child) override;
        void remove(ChildNode &child) override;

        UIWindow();
        virtual ~UIWindow();

    private:
        std::string m_id;
        ChildNode *m_child;
    };

}