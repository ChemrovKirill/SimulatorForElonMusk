#include <SFML/Graphics.hpp>
#include "Object.h"
#include "RigidBody.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(2400, 1200), "SimulatorForElonMask");

    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200) , 100, 50, 0, 1, 100, Vector2f(0.5, 0.5), 
        Vector2f(2, 1), Vector2f(0, 0), 20, 0));
    RigidBody Body2("test2.png", RigidBodyParameters(Vector2f(100, 1000) , 1000, 50, 0, 1, 2000, Vector2f(0.5, 0.5), 
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));

    Body2.AddForce(Force(false, 10, Vector2f(0, -1), Vector2f(0, 0)), 0);
    //Body2.AddForce(Force(false, 1, Vector2f(1, 0), Vector2f(0, 1)), 1);

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

        Body1.UpdatePosition(dt);
        Body2.UpdatePosition(dt);

        Body1.Draw(window);
        Body2.Draw(window);

        window.display();

        dt = deltaTime.restart().asSeconds();
    }

    return 0;
}