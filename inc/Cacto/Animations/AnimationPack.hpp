#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Animations/Export.hpp>

namespace cacto
{

    class Animation;

    template class CACTO_ANIMATIONS_API Pack<Animation>;

    class CACTO_ANIMATIONS_API AnimationPack
        : public virtual Pack<Animation>
    {

    public:
        const std::filesystem::path &getPath() const;
        
        const std::string &getId(const Animation &value) const override;
        const Animation *const getResource(const std::string &id) const override;

        AnimationPack(const std::filesystem::path &path);
        virtual ~AnimationPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<Animation>> m_map;
    };

    const std::string &CACTO_ANIMATIONS_API getId(const Animation &tileSet);
    const Animation *const CACTO_ANIMATIONS_API getAnimation(const std::string &id);

}
