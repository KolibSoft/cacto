#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Graphics/ImagePack.hpp>

namespace cacto
{

    const std::string &ImagePack::getId(const Shared<const sf::Image> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const sf::Image> ImagePack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto image = std::make_shared<sf::Image>();
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

    void ImagePack::setResource(const std::string &id, const Shared<const sf::Image> &value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                pair.second = value;
                return;
            }
        if (value)
        {
            auto path = m_path / id;
            auto _ = value->saveToFile(path);
            m_map.insert({id, value});
        }
        else
        {
            if (std::filesystem::remove(m_path / id))
                m_map.insert({id, nullptr});
        }
    }

    ImagePack::ImagePack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    ImagePack::~ImagePack() = default;

    const std::string &getId(const Shared<const sf::Image> &image)
    {
        auto &id = Pack<sf::Image>::id(image);
        return id;
    }

    Shared<const sf::Image> getImage(const std::string &id)
    {
        auto image = Pack<sf::Image>::resource(id);
        return std::move(image);
    }

    ImagePack Images{"."};

}