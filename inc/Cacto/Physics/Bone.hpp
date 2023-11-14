#ifndef CACTO_BONE_HPP
#define CACTO_BONE_HPP

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Physics/Export.hpp>

namespace cacto
{

    class CACTO_PHYSICS_API Bone
        : public sf::Transformable
    {

    public:
        void append(const sf::Vector2f &coord, Bone &bone);

        Bone();
        virtual ~Bone();

    private:
        struct Holder;

        std::vector<Holder> m_holders;

        struct Holder
        {
            sf::Vector2f coord;
            Bone *bone;
        };
    };

}

#endif