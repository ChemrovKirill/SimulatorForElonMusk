#include <SFML/Graphics.hpp>
#include "iostream"

#include "Object.h"
#include "RigidBody.h"
#include "Surface.h"
#include "Ship.h"

extern size_t screen_x;
extern size_t screen_y;
extern size_t window_x;
extern size_t window_y;

using namespace sf;

int main1() {
    RenderWindow window(VideoMode(window_x, window_y), "SimulatorForElonMask");

    RigidBody ShipBody("test2.png", RigidBodyParameters(Vector2f(200, 700), 100, 50, 0, 1, 100, Vector2f(0.5, 0.5),
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
    ShipBody.AddForce(Force(true, 500, Vector2f(0, -1), Vector2f(0.5, 0.5)), "Gravity");
    Object engine_object("test2.png", Vector2f(100, 100), 20, 40, 0);
    std::map<std::string, Engine> engines;
    engines["left"] = Engine(engine_object, Vector2f(0, 1), 0, 1000);
    engines["right"] = Engine(engine_object, Vector2f(1, 1), 0, 1000);

    Ship ship1(ShipBody, engines);

    Surface s;
    float dt = 0.01f;
    Clock deltaTime;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        ship1.Control();
        ship1.UpdatePosition(dt);

        s.Draw(window);
        ship1.Draw(window);

        window.display();

        dt = deltaTime.restart().asSeconds();
    }

    return 0;
}

int main() {
    RenderWindow window(VideoMode(window_x, window_y), "SimulatorForElonMask");

    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200) , 50, 200, 0, 0.4, 100, Vector2f(0.5, 0.5), 
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
    RigidBody Body2("test2.png", RigidBodyParameters(Vector2f(100, 1000) , 1000, 50, 0, 10, 2000, Vector2f(0.5, 0.5), 
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));

    Body2.AddForce(Force(false, 1000, Vector2f(0, -1), Vector2f(0, 0)), "0");
    //Body2.AddForce(Force(false, 1, Vector2f(1, 0), Vector2f(0, 1)), 1);

    Body1.AddForce(Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), "0");
    Body1.AddForce(Force(false, 400, Vector2f(0, 1), Vector2f(0.5, 0.5)), "1");
    Body1.AddForce(Force(false, 400, Vector2f(1, 0), Vector2f(0.5, 0.5)), "2");
    Body1.AddForce(Force(false, 400, Vector2f(-1, 0), Vector2f(0.5, 0.5)), "3");
    Body1.AddForce(Force(false, 200, Vector2f(-1, 0), Vector2f(0, 0)), "4");
    Body1.AddForce(Force(false, 200, Vector2f(1, 0), Vector2f(1, 1)), "5");
    Body1.AddForce(Force(false, 200, Vector2f(-1, 0), Vector2f(0, 1)), "6");
    Body1.AddForce(Force(false, 200, Vector2f(1, 0), Vector2f(1, 0)), "7");
    Body1.AddForce(Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)), "8");
    Body1.ForceOn("8");

    Surface s;
    float dt = 0, time = 0;
    Clock deltaTime;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            Body1.ForceOn("0");
        }
        else {
            Body1.ForceOff("0");
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            Body1.ForceOn("1");
        }
        else {
            Body1.ForceOff("1");
        }  
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            Body1.ForceOn("2");
        }
        else {
            Body1.ForceOff("2");
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            Body1.ForceOn("3");
        }
        else {
            Body1.ForceOff("3");
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            Body1.ForceOn("4");
            Body1.ForceOn("5");
        }
        else {
            Body1.ForceOff("4");
            Body1.ForceOff("5");
        }
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            Body1.ForceOn("6");
            Body1.ForceOn("7");
        }
        else {
            Body1.ForceOff("6");
            Body1.ForceOff("7");
        }
        


        Body1.UpdatePosition(dt);
        Body2.UpdatePosition(dt);

        Body1.Draw(window);
        Body1.DrawMassPosition(window);
        Body1.DrawBodyWay(window);
        Body1.DrawSpeed(window);
        Body1.DrawForce(window, Body1.GetForce("0"));
        Body1.DrawForce(window, Body1.GetForce("1"));
        Body1.DrawForce(window, Body1.GetForce("2"));
        Body1.DrawForce(window, Body1.GetForce("3"));
        Body1.DrawForce(window, Body1.GetForce("4"));
        Body1.DrawForce(window, Body1.GetForce("5"));
        Body1.DrawForce(window, Body1.GetForce("6"));
        Body1.DrawForce(window, Body1.GetForce("7"));
        Body1.DrawForce(window, Body1.GetForce("8"));
        //Body2.Draw(window);

        s.Draw(window);

        window.display();

        time += dt;
        dt = deltaTime.restart().asSeconds();
    }

    return 0;
}