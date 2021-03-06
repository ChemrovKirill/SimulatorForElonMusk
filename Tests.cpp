#include "Tests.h"

using namespace sf;

void test_menu() {
    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
    Menu(window);
}

void test_B2() {
    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");

    std::map<Hole, int> p = { { Hole::EMPTY_U, 0 },
                            { Hole::EMPTY_V, 0 },
                            { Hole::ICE, 50 },
                            { Hole::LAKE, 0 },
                            { Hole::METEORITE, 50 }
    };

    Surface s("surface.png", 20, 50, p, 70, 100, 50);
    float time = 0;
    float dt = 0;
    Clock deltaTime;

    RickAndMorty lander(Vector2f(0, s.YtoX(200) - 500));
    lander.AddMainForces(100);

    View view;

    view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
    view.setSize(sf::Vector2f(window_x(), window_y()));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();



        lander.control();
        lander.updateAirForce(1);



        lander.CollisionDetection(s, window);

        lander.UpdateShipPosition(dt);

        lander.DrawShip(window);


        lander.draw_all(window, true, true, false, true, true);

        view.setCenter(lander.GetCenterPosition());
        window.setView(view);

        s.Draw(window);
    


        window.display();

        time += dt;
        //std::cout << dt << std::endl;
        dt = deltaTime.restart().asSeconds();

        while (Keyboard::isKeyPressed(Keyboard::Space)) { dt = deltaTime.restart().asSeconds(); }

    }

}

//void Test5() {
//    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
//
//    Surface s("surface.png", 10);
//
//    Ship lander("Lunar_Lander_Mark1.png", RigidBodyParameters(Vector2f(200, s.YtoX(200) - 500), 170, 138, 0, 0.4, 100, Vector2f(0.5, 0.5),
//        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
//
//    lander.AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0.5, 1),
//        Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "down");
//    lander.AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0, 0.5),
//        Force(false, 400, Vector2f(-1, 0), Vector2f(0, 0.5)), 10), "left");
//    lander.AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(1, 0.5),
//        Force(false, 400, Vector2f(1, 0), Vector2f(1, 0.5)), 10), "right");
//    lander.AddForce("0", Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)));
//    lander.ForceOn("0");
//
//    float dt = 0, time = 0;
//    Clock deltaTime;
//
//    View view;
//    view.setCenter(Vector2f(window_x() / 2, window_y() / 2));
//    view.setSize(Vector2f(window_x(), window_y()));
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//                return;
//            }
//        }
//
//        window.clear();
//
//        if (Keyboard::isKeyPressed(Keyboard::W)) {
//            lander.ForceOn("down");
//        }
//        else {
//            lander.ForceOff("down");
//        }
//        if (Keyboard::isKeyPressed(Keyboard::A)) {
//            lander.ForceOn("left");
//        }
//        else {
//            lander.ForceOff("left");
//        }
//        if (Keyboard::isKeyPressed(Keyboard::D)) {
//            lander.ForceOn("right");
//        }
//        else {
//            lander.ForceOff("right");
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Num1)) {
//            lander.SetEngineThrust("down", 1);
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Num2)) {
//            lander.SetEngineThrust("down", 0.5);
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Num3)) {
//            lander.SetEngineThrust("down", 0.25);
//        }
//
//
//        lander.UpdateShipPosition(dt);
//        /* if (lander.CollisionDetection(s)) {
//             lander.Destroy();
//         }*/
//
//        lander.DrawShip(window);
//
//        lander.DrawMassPosition(window);
//        lander.DrawBodyWay(window);
//        lander.DrawSpeed(window);
//        lander.DrawForce(window, lander.GetForce("left"));
//        lander.DrawForce(window, lander.GetForce("right"));
//        lander.DrawForce(window, lander.GetForce("down"));
//
//        view.setCenter(lander.GetAbsMassPosition());
//        window.setView(view);
//
//        s.Update(dt);
//        s.Draw(window);
//
//        window.display();
//
//        time += dt;
//        dt = deltaTime.restart().asSeconds();
//    }
//
//}
//
//void Test4() {
//    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
//
//    Surface s("surface.png", 10);
//    float dt = 0, time = 0;
//    Clock deltaTime;
//
//    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200), 50, 200, 0, 0.4, 100, Vector2f(0.5, 0.5),
//        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
//    Body1.AddForce("0", Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)));
//    Body1.AddForce("1", Force(false, 400, Vector2f(0, 1), Vector2f(0.5, 0.5)));
//    Body1.AddForce("2", Force(false, 400, Vector2f(1, 0), Vector2f(0.5, 0.5)));
//    Body1.AddForce("3", Force(false, 400, Vector2f(-1, 0), Vector2f(0.5, 0.5)));
//
//
//    View view;
//    view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
//    view.setSize(sf::Vector2f(window_x(), window_y()));
//
//    while (window.isOpen())
//    {
//        Vector2i prev_mouse_pos;
//        Event event;
//        while (window.pollEvent(event))
//        {
//            switch (event.type)
//            {
//                // window closed
//            case sf::Event::Closed:
//                window.close();
//                break;
//
//                // key pressed
//            case sf::Event::KeyPressed:
//                if (event.key.code == sf::Keyboard::R) {
//                    s.Generate();
//                }
//                break;
//                // catch the resize events
//            case sf::Event::Resized:
//            {
//                // update the view to the new size of the window
//                //sf::FloatRect ResizedArea(0.f, 0.f, event.size.width, event.size.height);
//                view.setSize(event.size.width, event.size.height);
//                //window.setView(View(ResizedArea));
//                break;
//            }
//            default:
//                break;
//            }
//        }
//
//        window.clear();
//
//        if (Keyboard::isKeyPressed(Keyboard::Up)) {
//            view.move({ 0,-5 });
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down)) {
//            view.move({ 0 ,5 });
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Right)) {
//            view.move({ 5, 0 });
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            view.move({ -5, 0 });
//        }
//        window.setView(view);
//
//
//        if (Keyboard::isKeyPressed(Keyboard::W)) {
//            Body1.ForceOn("0");
//        }
//        else {
//            Body1.ForceOff("0");
//        }
//        if (Keyboard::isKeyPressed(Keyboard::S)) {
//            Body1.ForceOn("1");
//        }
//        else {
//            Body1.ForceOff("1");
//        }
//        if (Keyboard::isKeyPressed(Keyboard::D)) {
//            Body1.ForceOn("2");
//        }
//        else {
//            Body1.ForceOff("2");
//        }
//        if (Keyboard::isKeyPressed(Keyboard::A)) {
//            Body1.ForceOn("3");
//        }
//        else {
//            Body1.ForceOff("3");
//        }
//
//        Body1.UpdatePosition(dt);
//        //Body1.CollisionDetection(s);
//
//        Body1.Draw(window);
//        Body1.DrawMassPosition(window);
//        Body1.DrawBodyWay(window);
//        Body1.DrawSpeed(window);
//
//        s.Update(dt);
//        s.Draw(window);
//
//        window.display();
//
//        time += dt;
//        dt = deltaTime.restart().asSeconds();
//    }
//}
//
//void Test3() {
//    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
//
//    Surface s("surface.png", 10);
//    float dt = 0, time = 0;
//    Clock deltaTime;
//
//    sf::View view;
//    view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
//    view.setSize(sf::Vector2f(window_x(), window_y()));
//
//    while (window.isOpen())
//    {
//        Vector2i prev_mouse_pos;
//        Event event;
//        while (window.pollEvent(event))
//        {
//            switch (event.type)
//            {
//                // window closed
//            case sf::Event::Closed:
//                window.close();
//                break;
//
//                // key pressed
//            case sf::Event::KeyPressed:
//                if (event.key.code == sf::Keyboard::R) {
//                    s.Generate();
//                }
//                break;
//                // catch the resize events
//            case sf::Event::Resized:
//            {
//                // update the view to the new size of the window
//                //sf::FloatRect ResizedArea(0.f, 0.f, event.size.width, event.size.height);
//                view.setSize(event.size.width, event.size.height);
//                //window.setView(View(ResizedArea));
//                break;
//            }
//            default:
//                break;
//            }
//        }
//
//        window.clear();
//
//        if (Keyboard::isKeyPressed(Keyboard::Up)) {
//            view.move({ 0,-2 });
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down)) {
//            view.move({ 0 ,2 });
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Right)) {
//            view.move({ 2, 0 });
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            view.move({ -2, 0 });
//        }
//        window.setView(view);
//
//
//        s.Draw(window);
//
//        window.display();
//
//        time += dt;
//        dt = deltaTime.restart().asSeconds();
//    }
//}

//void Test2() {
//    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
//
//    RigidBody Body1("test2.png", RigidBodyParameters(Vector2f(200, 200), 50, 200, 0, 0.4, 100, Vector2f(0.5, 0.5),
//        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
//

//void Test1() {
//    RenderWindow window(VideoMode(window_x(), window_y()), "SimulatorForElonMask");
//
//    RigidBody ShipBody("test2.png", RigidBodyParameters(Vector2f(200, 700), 100, 50, 0, 1, 100, Vector2f(0.5, 0.5),
//        Vector2f(0, 0), Vector2f(0, 0), 0, 0));
//    ShipBody.AddForce("Gravity", Force(true, 500, Vector2f(0, -1), Vector2f(0.5, 0.5)));
//    Object engine_object("test2.png", Vector2f(100, 100), 20, 40, 0);
//    std::map<std::string, Engine> engines;
//    engines["left"] = Engine(engine_object, Vector2f(0, 1), 0, 1000);
//    engines["right"] = Engine(engine_object, Vector2f(1, 1), 0, 1000);
//
//    Ship ship1(ShipBody, engines);
//
//    Surface s("surface.png", 10);
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
//}