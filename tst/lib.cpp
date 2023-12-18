#include <string>
#include <Cacto/Config.hpp>

extern "C"
{

    std::string *CACTO_API_EXPORT dynamicTest(const std::string *string)
    {
        return new std::string("It Works: " + *string);
    };
    
}