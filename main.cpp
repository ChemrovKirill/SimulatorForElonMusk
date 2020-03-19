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

void Surface::Draw(RenderWindow& window) const {
    window.draw(surface, &texture);
}

using namespace sf;

//int main1() {
//    RenderWindow window(VideoMode(window_x, window_y), "SimulatorForElonMask");
//
//    RigidBody ShipBody("test2.png", RigidBodyParameters(Vector2f(200, 700), 100, 50, 0, 1, 100, Vector2f(0.5, 0.5),
//        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
//    ShipBody.AddForce(Force(true, 500, Vector2f(0, -1), Vector2f(0.5, 0.5)), "Gravity");
//    Object engine_object("test2.png", Vector2f(100, 100), 20, 40, 0);
//    std::map<std::string, Engine> engines;
//    engines["left"] = Engine(engine_object, Vector2f(0, 1), 1000);
//    engines["right"] = Engine(engine_object, Vector2f(1, 1), 1000);
//
//    Ship ship1(ShipBody, engines);
//
//    Surface s;
//    float dt = 0.01f;
//    Clock deltaTime;
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        ship1.Control();
//        ship1.UpdatePosition(dt);
//
//        s.Draw(window);
//        ship1.Draw(window);
//
//        window.display();
//
//        dt = deltaTime.restart().asSeconds();
//    }
//
//    return 0;
//}


void test1() {
    RenderWindow window(VideoMode(window_x, window_y), "SimulatorForElonMask");

    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200), 50, 200, 0, 0.4, 100, Vector2f(0.5, 0.5),
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
    RigidBody Body2("test2.png", RigidBodyParameters(Vector2f(100, 1000), 1000, 50, 0, 10, 2000, Vector2f(0.5, 0.5),
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));

    Body2.AddForce("0", Force(false, 1000, Vector2f(0, -1), Vector2f(0, 0)));
    //Body2.AddForce(Force(false, 1, Vector2f(1, 0), Vector2f(0, 1)), 1);

    Body1.AddForce("0", Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)));
    Body1.AddForce("1", Force(false, 400, Vector2f(0, 1), Vector2f(0.5, 0.5)));
    Body1.AddForce("2", Force(false, 400, Vector2f(1, 0), Vector2f(0.5, 0.5)));
    Body1.AddForce("3", Force(false, 400, Vector2f(-1, 0), Vector2f(0.5, 0.5)));
    Body1.AddForce("4", Force(false, 200, Vector2f(-1, 0), Vector2f(0, 0)));
    Body1.AddForce("5", Force(false, 200, Vector2f(1, 0), Vector2f(1, 1)));
    Body1.AddForce("6", Force(false, 200, Vector2f(-1, 0), Vector2f(0, 1)));
    Body1.AddForce("7", Force(false, 200, Vector2f(1, 0), Vector2f(1, 0)));
    Body1.AddForce("8", Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)));
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
}

void test2() {
    RenderWindow window(VideoMode(window_x, window_y), "SimulatorForElonMask");

    Ship lander("test2.png", RigidBodyParameters(Vector2f(200, 200), 50, 200, 0, 0.4, 100, Vector2f(0.5, 0.5),
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
    
    lander.AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0.5, 1), 
                     Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)),      10) , "1");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0, 0), 
                     Force(false, 200, Vector2f(-1, 0), Vector2f(0, 0)),     10) , "3");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(1, 0), 
                     Force(false, 200, Vector2f(1, 0), Vector2f(1, 0)),     10) , "4");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(1, 1), 
                     Force(false, 200, Vector2f(1, 0), Vector2f(1, 1)),     10) , "5");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0, 1), 
                     Force(false, 200, Vector2f(-1, 0), Vector2f(0, 1)),     10) , "6");
    lander.AddForce("0", Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)));
    lander.ForceOn("0");


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
            lander.ForceOn("1");
        }
        else {
            lander.ForceOff("1");
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            lander.ForceOn("3");
            lander.ForceOn("5");
        }
        else {
            lander.ForceOff("3");
            lander.ForceOff("5");
        }        
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            lander.ForceOn("4");
            lander.ForceOn("6");
        }
        else {
            lander.ForceOff("4");
            lander.ForceOff("6");
        }

        lander.UpdateShipPosition(dt);

        lander.DrawShip(window);

        lander.DrawMassPosition(window);
        lander.DrawBodyWay(window);
        lander.DrawSpeed(window);
        lander.DrawForce(window, lander.GetForce("1"));
        lander.DrawForce(window, lander.GetForce("3"));
        lander.DrawForce(window, lander.GetForce("4"));
        lander.DrawForce(window, lander.GetForce("5"));
        lander.DrawForce(window, lander.GetForce("6"));
        lander.DrawForce(window, lander.GetForce("0"));

        s.Draw(window);

        window.display();

        time += dt;
        dt = deltaTime.restart().asSeconds();
    }

}

int main() {
    test2();

    return 0;
}