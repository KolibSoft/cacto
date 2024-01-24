#include <SFML/Window/Event.hpp>
#include <Cacto/Window/NodeUtils.hpp>
#include <Cacto/UI/NodeUtils.hpp>
#include <Cacto/UI/UIWindow.hpp>

namespace cacto
{

    const std::string &UIWindow::getId() const
    {
        return m_id;
    }

    UIWindow &UIWindow::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    szt UIWindow::getChildCount() const
    {
        return m_child ? 1 : 0;
    }

    ChildNode *const UIWindow::getChild(szt index) const
    {
        return index == 0 ? m_child : nullptr;
    }

    void UIWindow::showContent()
    {
        clear();
        if (m_child)
            cacto::draw(*m_child, *this);
        display();
    }

    sf::Vector2f UIWindow::compact()
    {
        sf::Vector2f size(getSize());
        if (m_child)
            cacto::compact(*m_child);
        return size;
    }

    sf::Vector2f UIWindow::inflate(const sf::Vector2f &containerSize)
    {
        sf::Vector2f size(getSize());
        if (m_child)
            cacto::inflate(*m_child, size);
        return size;
    }

    void UIWindow::place(const sf::Vector2f &position)
    {
        if (m_child)
            cacto::place(*m_child, {0, 0});
    }

    void UIWindow::inflateContent()
    {
        compact();
        inflate();
        place();
    }

    bool UIWindow::handle(const sf::Event &event)
    {
        auto handled = m_child && cacto::handle(*m_child, event);
        return handled;
    }

    bool UIWindow::bubble(Node &target, const sf::Event &event)
    {
        return false;
    }

    void UIWindow::handleContent()
    {
        sf::Event event{};
        while (pollEvent(event) && !handle(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
                continue;
            }
            if (event.type == sf::Event::Resized)
            {
                setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
                continue;
            }
        }
    }

    void UIWindow::append(ChildNode &child)
    {
        if (m_child == &child)
            return;
        if (m_child != nullptr)
            throw std::runtime_error("This node has already another child");
        if (child.getParent() != nullptr && child.getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
        if (hasAncestor(child))
            throw std::runtime_error("The node is an ancestor");
        m_child = &child;
        child.attach(*this);
    }

    void UIWindow::remove(ChildNode &child)
    {
        if (m_child == &child)
        {
            m_child = nullptr;
            child.detach();
        }
    }

    UIWindow::UIWindow()
        : sf::RenderWindow(),
          m_id(),
          m_child()
    {
    }

    UIWindow::~UIWindow()
    {
        if (m_child)
            remove(*m_child);
    }

}