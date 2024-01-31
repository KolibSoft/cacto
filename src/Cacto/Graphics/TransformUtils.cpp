#include <sstream>
#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Core/AngleUtils.hpp>
#include <Cacto/Graphics/TransformPrinter.hpp>
#include <Cacto/Graphics/TransformScanner.hpp>
#include <Cacto/Graphics/TransformUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Transform &transform)
    {
        std::stringstream stream{};
        stream << transform;
        auto string = stream.str();
        return std::move(string);
    }

    sf::Transform toTransform(const std::string &string)
    {
        sf::Transform transform{};
        std::stringstream stream{string};
        stream >> transform;
        return std::move(transform);
    }

    XmlValue toXml(const sf::Transform &transform)
    {
        XmlValue xml{"Transform", {}};
        xml["matrix"] = toString(transform);
        return std::move(xml);
    }

    sf::Transform toTransform(const XmlValue &xml)
    {
        sf::Transform transform = {};
        auto matrix = xml.getAttribute("matrix", "1,0,0,0,1,0,0,0,1");
        transform = toTransform(matrix);
        if (xml.isTag())
            for (auto &item : xml.asContent())
                if (item.isTag())
                {
                    if (item.getName() == "Scale")
                    {
                        auto factors = toVector(item.getAttribute("factors", "1,1"));
                        transform.scale(factors);
                    }
                    else if (item.getName() == "Translate")
                    {
                        auto offset = toVector(item.getAttribute("offset", "0,0"));
                        transform.translate(offset);
                    }
                    else if (item.getName() == "Rotate")
                    {
                        auto angle = toAngle(item.getAttribute("angle", "0deg"));
                        transform.rotate(angle);
                    }
                }
        return std::move(transform);
    }

    std::ostream &operator<<(std::ostream &stream, const sf::Transform &transform)
    {
        Printer printer{stream};
        TransformPrinter tprinter{printer};
        tprinter.printTransform(transform);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::Transform &transform)
    {
        Scanner scanner{stream};
        TransformScanner tscanner{scanner};
        tscanner.scanTransform(transform);
        return stream;
    }

}