#include <iostream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/Straight.hpp>
#include <Cacto/Graphics/Bezier.hpp>

int main()
{

    {
        cacto::Line *line = new cacto::Straight({10, 10}, {100, 100});
        auto json = cacto::toJson(line);
        std::cout << json.toString() << "\n";

        delete line;
        line = nullptr;
        cacto::fromJson(line, json);
        json = cacto::toJson(line);
        std::cout << json.toString() << "\n";
    }

    {
        cacto::Line *line = new cacto::Bezier({{20, 20}, {200, 200}});
        auto json = cacto::toJson(line);
        std::cout << json.toString() << "\n";

        delete line;
        line = nullptr;
        cacto::fromJson(line, json);
        json = cacto::toJson(line);
        std::cout << json.toString() << "\n";
    }

    return 0;
}