#include <SFML/Graphics.hpp>
#include "Object.h"
#include "RigidBody.h"
#include "Surface.h"

using namespace sf;

int main() {
    RenderWindow window(sf::VideoMode(1400, 700), "SFML works!");
    //sf::CircleShape shape(200.f);
    //shape.setFillColor(sf::Color::Red);

    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200) , 100, 50, 0, 1, 1, Vector2f(0.5, 0.5), 
        Vector2f(2, 1), Vector2f(0.2, 0.1), 10, 0.1));
    RigidBody Body2("test2.png", RigidBodyParameters(Vector2f(100, 100) , 100, 50, 0, 1, 1, Vector2f(0.5, 0.5), 
        Vector2f(2, 1), Vector2f(0, 0), 10, 0));

    Surface s;

    while (window.isOpen())
    {

        Clock deltaTime; float dt = 0.01f;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);

        Body1.UpdatePosition(dt);
        Body1.Draw(window);

        Body2.UpdatePosition(dt);
        Body2.Draw(window);

        s.Draw(window);

        window.display();

        dt = deltaTime.restart().asSeconds();
    }

    return 0;
}