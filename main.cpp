#include "Cone.hpp"
#include "Cube.hpp"
#include "FigureCollection.hpp"
#include "Sphere.hpp"

#include <iostream>
#include <memory>
#include <sstream>

int main() {
    FigureCollection figures;

    auto sphere = std::make_unique<Sphere>(2.0);
    figures.add(sphere.get());
    sphere.release();

    auto cube = std::make_unique<Cube>(3.0);
    figures.add(cube.get());
    cube.release();

    auto cone = std::make_unique<Cone>();
    std::istringstream input("3 4");
    input >> *cone;
    figures.add(cone.get());
    cone.release();

    for (std::size_t i = 0; i < figures.size(); ++i) {
        Figure& figure = figures[i];
        std::cout << figure << '\n';

        if (auto* s = dynamic_cast<Sphere*>(&figure)) {
            std::cout << "Radius: " << s->radius() << '\n';
        } else if (auto* c = dynamic_cast<Cube*>(&figure)) {
            std::cout << "Edge: " << c->edge() << '\n';
        } else if (auto* c = dynamic_cast<Cone*>(&figure)) {
            std::cout << "Slant height: " << c->slantHeight() << '\n';
        }
    }

    std::cout << "Total volume: " << figures.totalMetric() << '\n';
    std::cout << "First volume: " << static_cast<double>(figures[0]) << '\n';
    std::cout << "First and second volumes equal: "
              << std::boolalpha << (figures[0] == figures[1]) << '\n';

    FigureCollection copy = figures;
    copy.remove(0);
    std::cout << "Original size: " << figures.size() << '\n';
    std::cout << "Copy size after removal: " << copy.size() << '\n';
}
