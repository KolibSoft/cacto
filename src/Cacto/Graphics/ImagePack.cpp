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
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const sf::Image *const ImagePack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto image = std::make_shared<sf::Image>();
            auto _ = image->loadFromFile(path);
            m_map.insert({id, image});
            return image.get();
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

    ImagePack::~ImagePack() = default;

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

    const std::string &getId(const sf::Image &image)
    {
        auto &id = Pack<sf::Image>::id(image);
        return id;
    }

    const sf::Image *const getImage(const std::string &id)
    {
        auto image = Pack<sf::Image>::resource(id);
        return image;
    }

}