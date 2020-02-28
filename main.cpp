#include <SFML/Graphics.hpp>
#include "Object.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Red);

    Object test_object_1("test.png", 100, 100, 100, 50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);

        test_object_1.Draw(window);

        window.display();
    }

    return 0;
}