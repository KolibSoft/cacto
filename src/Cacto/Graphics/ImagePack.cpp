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
            auto _ =  value.saveToFile(m_path / key);
        *image = value;
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

}