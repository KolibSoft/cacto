#include <iostream>
#include <vector>
#include <Cacto/Core/Reference.hpp>

class Ax
{

public:
    int value{};

    Ax()
    {
        std::cout << "Created\n";
    }

    ~Ax()
    {
        std::cout << "Destroyed\n";
    }
};

int main()
{

    std::vector<cacto::Reference<Ax>> vector{};
    vector.push_back(Ax());
    vector.push_back(Ax());
    vector.push_back(Ax());
    vector.push_back(Ax());

    cacto::Reference<Ax> ax = nullptr;

    return 0;
}