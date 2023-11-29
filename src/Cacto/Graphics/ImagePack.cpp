#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Graphics/ImagePack.hpp>

namespace cacto
{

    const std::filesystem::path &ImagePack::getPath() const
    {
        return m_path;
    }

    void ImagePack::setPath(const std::filesystem::path &value)
    {
        m_path = value;
    }

    const std::string *const ImagePack::getKey(const sf::Image *const value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return &pair.first;
        return nullptr;
    }

    const sf::Image &ImagePack::getImage(const std::string &key, bool refresh) const
    {
        auto &image = m_map[key];
        if (image == nullptr)
            refresh = image = new sf::Image();
        if (refresh)
            auto _ = image->loadFromFile(m_path / key);
        return *image;
    }

    void ImagePack::setImage(const std::string &key, const sf::Image &value, bool refresh)
    {
        auto &image = m_map[key];
        if (image == nullptr)
            refresh = image = new sf::Image();
        if (refresh)
            auto _ = value.saveToFile(m_path / key);
        *image = value;
    }

    void ImagePack::refreshToFiles() const
    {
        for (auto &pair : m_map)
            if (pair.second)
                auto _ = pair.second->saveToFile(m_path / pair.first);
    }

    void ImagePack::refreshFromFiles()
    {
        for (auto &pair : m_map)
            if (pair.second)
                auto _ = pair.second->loadFromFile(m_path / pair.first);
    }

    ImagePack::ImagePack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    ImagePack::~ImagePack()
    {
        for (auto &pair : m_map)
        {
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
        }
    }

    const std::string *const getKey(const sf::Image *const value)
    {
        if (ImagePacks.size() == 0)
            throw std::runtime_error("There are not image packs");
        for (auto &pair : ImagePacks)
        {
            auto key = pair.second.getKey(value);
            if (key)
                return key;
        }
        return nullptr;
    }

    const sf::Image &getImage(const std::string &key)
    {
        if (ImagePacks.size() == 0)
            throw std::runtime_error("There are not image packs");
        const sf::Image *image = nullptr;
        for (auto &pair : ImagePacks)
        {
            image = &pair.second.getImage(key);
            if (image->getSize() != sf::Vector2u{0, 0})
                break;
        }
        return *image;
    }

    std::unordered_map<std::string, ImagePack> ImagePacks{};

}