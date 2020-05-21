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
}


void RickAndMorty::control() {
    if (status != 0 && status != 1) {
        for (auto& i : engines) { EngineOff(i.first); }
        return;
    }

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        EngineOn("down");
    }
    else {
        EngineOff("down");
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        EngineOn("left");
    }
    else {
        EngineOff("left");
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        EngineOn("right");
    }
    else {
        EngineOff("right");
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

