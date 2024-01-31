#include <Cacto/Core/Morph.hpp>

class MorphClass
    : public virtual cacto::Morph
{
public:
    int value{};
};

class SubMorphClass
    : public MorphClass
{
public:
    int subValue{};
};

int main()
{

    MorphClass *instance = new SubMorphClass();
    instance->ptr<SubMorphClass>()->subValue = 32;
    auto result = instance->ref<SubMorphClass>().subValue;

    return 0;
}