#include <fstream>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Animations/Animation.hpp>
#include <Cacto/Animations/AnimationPack.hpp>

namespace cacto
{

    const std::filesystem::path &AnimationPack::getPath() const
    {
        return m_path;
    }

    const std::string &AnimationPack::getId(const Animation &value) const
    {
        for (auto &pair : m_map)
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const Animation *const AnimationPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            Animation *animation = nullptr;
            XmlValue xml = nullptr;
            xml.fromFile(path);
            animation = cacto::fromXml<Animation>(xml);
            m_map.insert({id, std::shared_ptr<Animation>(animation)});
            return animation;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    AnimationPack::AnimationPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    AnimationPack::~AnimationPack() = default;

    AnimationPack::AnimationPack(AnimationPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    AnimationPack &AnimationPack::operator=(AnimationPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

}