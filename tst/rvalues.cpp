#include <iostream>

class Example
{

public:
    int value{};

    Example &test() &
    {
        value += 1;
        std::cout << "LVALUE: " << value << "\n";
        return *this;
    }

    Example &&test() &&
    {
        value += 1;
        std::cout << "RVALUE: " << value << "\n";
        return std::move(*this);
    }
};

void test(const Example &instance)
{
    std::cout << "Instance borrowed\n";
}

void test(Example &&instance)
{
    std::cout << "Instance owned\n";
}

int main()
{
    Example instance{};
    test(Example().test().test());
    test(instance.test().test());
    test(instance = Example().test().test());
    return 0;
}