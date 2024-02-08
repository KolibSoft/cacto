#include <iostream>

class Base
{

public:
    int value{};

    virtual void fx()
    {
        std::cout << "BASE\n";
    }
};

class Derived : public Base
{

public:
    int otherValue{};

    void fx() override
    {
        std::cout << "DERIVED\n";
    }
};

int main()
{

    Derived derived{};
    derived.value = 4;
    derived.otherValue = 5;
    derived.fx();

    Base &base = derived;
    base.value = 8;
    base.fx();

    base = Base();
    base.fx();

    return 0;
}