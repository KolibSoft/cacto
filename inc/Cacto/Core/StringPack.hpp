#ifndef CACTO_STRING_PACK_HPP
#define CACTO_STRING_PACK_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Export.hpp>

namespace sf
{
    class String;
}

namespace cacto
{

    class CACTO_CORE_API StringPack
    {

    public:
        const std::filesystem::path &getPath() const;
        void setPath(const std::filesystem::path &value);

        const std::string *const getKey(const sf::String *const value) const;

        const sf::String &getString(const std::string &key, bool refresh = false) const;
        void setString(const std::string &key, const sf::String &value, bool refresh = false);

        void refreshToFiles() const;
        void refreshFromFiles();

        StringPack(const std::filesystem::path &path = ".");
        virtual ~StringPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::String *> m_map;
    };

    const std::string *const CACTO_CORE_API getKey(const sf::String *const value);
    const sf::String &CACTO_CORE_API getString(const std::string &key);

    extern std::unordered_map<std::string, StringPack> CACTO_CORE_API StringPacks;

}

#endif