#include <iostream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/Straight.hpp>
#include <Cacto/Graphics/Bezier.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Triangle.hpp>

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

    {
        cacto::Geometry *geometry = new cacto::Rectangle({{20, 20}, {200, 200}});
        auto json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";

        delete geometry;
        geometry = nullptr;
        cacto::fromJson(geometry, json);
        json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";
    }

    {
        cacto::Geometry *geometry = new cacto::Ellipse({{20, 20}, {200, 200}});
        auto json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";

        delete geometry;
        geometry = nullptr;
        cacto::fromJson(geometry, json);
        json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";
    }

    {
        cacto::Geometry *geometry = new cacto::Triangle({{20, 20}, {200, 200}, {150, 150}});
        auto json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";

        delete geometry;
        geometry = nullptr;
        cacto::fromJson(geometry, json);
        json = cacto::toJson(geometry);
        std::cout << json.toString() << "\n";
    }

    std::cout << "Line converters: " << cacto::JsonConverter<cacto::Line>::Converters.size() << "\n";
    std::cout << "Line geometry: " << cacto::JsonConverter<cacto::Geometry>::Converters.size() << "\n";

    return 0;
}