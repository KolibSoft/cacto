#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Core/Export.hpp>

namespace sf
{
    class String;
}

namespace cacto
{

    template class CACTO_CORE_API Pack<sf::String>;

    class CACTO_CORE_API StringPack
        : public virtual Pack<sf::String>
    {

    public:
        const std::string &getId(const Shared<const sf::String> &value) const override;
        Shared<const sf::String> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const sf::String> &value) override;

        StringPack(const std::filesystem::path &path);
        virtual ~StringPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const sf::String>> m_map;
    };

    const std::string &CACTO_CORE_API getId(const Shared<const sf::String> &string);
    Shared<const sf::String> CACTO_CORE_API getString(const std::string &id);

}
