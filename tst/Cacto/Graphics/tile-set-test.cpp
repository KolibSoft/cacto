#include <Cacto/Graphics/TileSet.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    cacto::TexturePack textures{"."};

    cacto::TileSet tileSet{};
    cacto::fromXmlFile(tileSet, "res/tile_set.xml");
    cacto::toXmlFile(tileSet, "res/tile_set.xml", 4);

    return 0;
}