#include <iostream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/Straight.hpp>

int main()
{

    cacto::Line *line = new cacto::Straight({10, 10}, {100, 100});
    auto json = cacto::toJson(line);
    std::cout << json.toString() << "\n";

    delete line;
    line = nullptr;
    cacto::fromJson(line, json);
    auto &straight = *dynamic_cast<cacto::Straight *>(line);

    return 0;
}