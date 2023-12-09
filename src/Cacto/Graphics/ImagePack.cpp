#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Graphics/ImagePack.hpp>

namespace cacto
{

    const std::string *const ImagePack::getId(const sf::Image &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return &pair.first;
        return nullptr;
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

    void ImagePack::setResource(const std::string &id, const sf::Image *const value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                if (pair.second && value)
                {
                    *pair.second = *value;
                }
                else if (pair.second && !value)
                {
                    delete pair.second;
                    pair.second = nullptr;
                }
                else if (!pair.second && value)
                {
                    pair.second = new sf::Image(*value);
                }
                return;
            }
        if (value)
        {
            auto path = m_path / id;
            auto image = new sf::Image(*value);
            auto _ = image->saveToFile(path);
            m_map.insert({id, image});
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

    const std::string *const getId(const sf::Image &string)
    {
        for (auto &pack : Pack<sf::Image>::Packs)
        {
            auto id = pack->getId(string);
            if (id)
                return id;
        }
        return nullptr;
    }

    const sf::Image *const getImage(const std::string &id)
    {
        for (auto &pack : Pack<sf::Image>::Packs)
        {
            auto string = pack->getResource(id);
            if (string)
                return string;
        }
        return nullptr;
    }

}