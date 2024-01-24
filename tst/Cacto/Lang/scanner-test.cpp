#include <sstream>
#include <iostream>
#include <fstream>
#include <Cacto/Lang/Scannable.hpp>
#include <Cacto/Lang/Scanner.hpp>

class ScannableClass : public cacto::Scannable
{

public:
    std::string key{};
    int value{};

    bool scan(cacto::Scanner &scanner) override
    {
        scanner.dropBlankln();
        if (scanner.dropToken("{"))
        {
            scanner.dropBlankln();
            if (scanner.dropToken("\"") && scanner.scanWord())
            {
                auto key = scanner.take();
                if (scanner.dropToken("\""))
                {
                    scanner.dropBlankln();
                    if (scanner.dropToken(":"))
                    {
                        scanner.dropBlankln();
                        if (scanner.scanDigit())
                        {
                            auto value = std::stoi(scanner.take());
                            scanner.dropBlankln();
                            if (scanner.dropToken("}"))
                            {
                                this->key = key;
                                this->value = value;
                                return true;
                            }
                        }
                    }
                }
            }
        }
        throw std::runtime_error("Format Error");
    }
};

int main()
{

    ScannableClass scannable{};
    std::ifstream fstream{"res/file.txt"};
    fstream >> scannable;

    return 0;
}