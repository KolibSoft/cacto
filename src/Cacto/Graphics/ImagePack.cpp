#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Graphics/ImagePack.hpp>

namespace cacto
{

    const std::filesystem::path &ImagePack::getPath() const
    {
        return m_path;
    }

    const std::string &ImagePack::getId(const sf::Image &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return pair.first;
        return NoId;
    }

    const sf::Image *const ImagePack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto image = new sf::Image();
            auto _ = image->loadFromFile(path);
            m_map.insert({id, image});
            return image;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    ImagePack::ImagePack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    ImagePack::~ImagePack()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
    }

    ImagePack::ImagePack(ImagePack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    ImagePack &ImagePack::operator=(ImagePack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

}