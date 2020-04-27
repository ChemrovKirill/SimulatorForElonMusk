#include "RickAndMorty.h"

RickAndMorty::RickAndMorty(sf::Vector2f position) : Ship("Rick&Morty.png", download(position)) {
    assembly();
}

RigidBodyParameters RickAndMorty::download(sf::Vector2f position) {
    std::ifstream fin("data/Rick&Morty.txt");
    if (!fin.is_open()) { throw "Wrong file name"; }
    RigidBodyParameters par;
    par.position = position;
    std::string str;
    float x, y;
    fin >> str >> par.width;
    fin >> str >> par.height;
    fin >> str >> par.angle;
    fin >> str >> par.mass;
    fin >> str >> par.moment_of_inertia;
    fin >> str >> x >> y;
    par.mass_position = Vector2f(x, y);
    fin.close();
    return par;
}

void RickAndMorty::assembly() {
    AddEngine(Engine(Object("Plumbus.png", Vector2f(10, 10), 40, 80, 0), Vector2f(0.5, 1),
        Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "down");
    AddEngine(Engine(Object("Plumbus.png", Vector2f(10, 10), 40, 80, 0), Vector2f(0, 0.5),
        Force(false, 100, Vector2f(0, -1), Vector2f(0, 0.5)), 10), "left");
    AddEngine(Engine(Object("Plumbus.png", Vector2f(10, 10), 40, 80, 0), Vector2f(1, 0.5),
        Force(false, 100, Vector2f(0, -1), Vector2f(1, 0.5)), 10), "right");
    AddForce("G", Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)));
    ForceOn("G");

    AddForce("Air", Force(false, sqal(velocity), Vector2f(0, 0), Vector2f(0.5, 0.5)));
    ForceOn("Air");
}

void RickAndMorty::updateAirForce(float k) {
    forces["Air"].force = k * sqal(velocity) / 10;
    if (sqal(velocity) > 1) {
        forces["Air"].force_vector = -rotate_to_angle(velocity, -GetAngle() * RAD) / sqal(velocity);
    }
    else {
        forces["Air"].force_vector = -rotate_to_angle(velocity, -GetAngle() * RAD);
    }
}


void RickAndMorty::control() {
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        ForceOn("down");
    }
    else {
        ForceOff("down");
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        ForceOn("left");
    }
    else {
        ForceOff("left");
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        ForceOn("right");
    }
    else {
        ForceOff("right");
    }
        
    if (Keyboard::isKeyPressed(Keyboard::Num1)) {
        SetEngineThrust("down", 1);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num2)) {
        SetEngineThrust("down", 0.5);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num3)) {
        SetEngineThrust("down", 0.25);
    }
}

void RickAndMorty::draw_all(RenderWindow& window, bool position, bool speed, bool way, bool forces, bool collision) {

    if (position == true) {
        DrawMassPosition(window);
    }
    if (way == true) {
        DrawBodyWay(window);
    }
    if (speed == true) {
        DrawSpeed(window);
    }
    if (forces == true) {
        DrawForce(window, GetForce("1"));
        DrawForce(window, GetForce("3"));
        DrawForce(window, GetForce("4"));
        DrawForce(window, GetForce("5"));
        DrawForce(window, GetForce("6"));
        DrawForce(window, GetForce("G"));
        DrawForce(window, GetForce("Air"));
    }
    if (collision == true) {
        CollisionModelDrow(window);
    }
}

