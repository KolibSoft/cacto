#include <iostream>

#include <SFML/System/String.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <Cacto/Core/StringPack.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Core/RootNode.hpp>

class IsolatedNode
    : public virtual cacto::RootNode,
      public virtual cacto::LeafNode
{
};

namespace isolated
{
    class XmlConverter
        : public cacto::node::XmlConverter
    {

    public:
        cacto::XmlValue toXml(const cacto::Node *const node) const override
        {
            const IsolatedNode *isolated = nullptr;
            if (node && (isolated = dynamic_cast<const IsolatedNode *>(node)))
            {
                cacto::XmlValue xml{"Isolated", {}};
                return std::move(xml);
            }
            return nullptr;
        }

        cacto::Node *fromXml(const cacto::XmlValue &xml) const override
        {
            if (xml.isTag() && xml.getName() == "Isolated")
            {
                auto isolated = new IsolatedNode();
                return isolated;
            }
            return nullptr;
        }
    } Converter{};
}

int main()
{

    cacto::XmlValue xml = nullptr;
    xml.fromString("<Isolated/>");
    auto node = cacto::XmlConverter<cacto::Node>::value(xml);
    IsolatedNode &isolated = *dynamic_cast<IsolatedNode *>(node);

    cacto::StringPack pack{"res/strings"};
    sf::String string = "My String Basic";

    pack.setResource("my_string.txt", &string);
    std::cout << "Content: " << pack.getResource("my_string.txt")->toAnsiString() << "\n";

    string = "My String Content";
    pack.setResource("my_string.txt", &string);
    std::cout << "Content: " << pack.getResource("my_string.txt")->toAnsiString() << "\n";

    auto resource = cacto::Pack<sf::String>::resource("my_string.txt");
    std::cout << "Global Content: " << resource->toAnsiString() << "\n";
    std::cout << "Global Id: " << *cacto::Pack<sf::String>::id(*resource) << "\n";

    return 0;
}