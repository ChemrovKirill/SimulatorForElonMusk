#include "Lunar_Lander_Mark1_STM32.h"

Lunar_Lander_Mark1_STM32::Lunar_Lander_Mark1_STM32(sf::Vector2f position) : Ship("Lunar_Lander_Mark1.png", download(position)) {
    assembly();
}

RigidBodyParameters Lunar_Lander_Mark1_STM32::download(sf::Vector2f position) {
    std::ifstream fin("data/Lunar_Lander_Mark1.txt");
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

void Lunar_Lander_Mark1_STM32::assembly() {
    AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0.4, 1),
        Force(false, 400, Vector2f(0, -1), Vector2f(0.4, 1)), 10), "1");
    AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0.6, 1),
        Force(false, 400, Vector2f(0, -1), Vector2f(0.6, 1)), 10), "2");
    AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0.3, 0.25),
        Force(false, 200, Vector2f(1, 0), Vector2f(0.25, 0.25)), 10), "3");
    AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0.7, 0.25),
        Force(false, 200, Vector2f(-1, 0), Vector2f(0.75, 0.25)), 10), "4");
    AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0.3, 0.75),
        Force(false, 200, Vector2f(1, 0), Vector2f(0.3, 0.75)), 10), "5");
    AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0.7, 0.75),
        Force(false, 200, Vector2f(-1, 0), Vector2f(0.7, 0.75)), 10), "6");
}

void Lunar_Lander_Mark1_STM32::control() {}

void Lunar_Lander_Mark1_STM32::control_STM(const Lander_Parametr& par)
{
    if (Keyboard::isKeyPressed(Keyboard::W) || par.en_stat[0] == 1) {
        ForceOn("1");
        ForceOn("2");
    }
    else {
        EngineOff("1");
        EngineOff("2");
    }
    if (Keyboard::isKeyPressed(Keyboard::E) || par.en_stat[1] == 1) {
        EngineOn("3");
        EngineOn("6");
    }
    else {
        EngineOff("3");
        EngineOff("6");
    }
    if (Keyboard::isKeyPressed(Keyboard::Q) || par.en_stat[2] == 1) {
        EngineOn("5");
        EngineOn("4");
    }
    else {
        EngineOff("5");
        EngineOff("4");
    }
    if (Keyboard::isKeyPressed(Keyboard::Num1)) {
        SetEngineThrust("1", 1);
        SetEngineThrust("2", 1);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num2)) {
        SetEngineThrust("1", 0.5);
        SetEngineThrust("2", 0.5);
    }
    if (Keyboard::isKeyPressed(Keyboard::Num3)) {
        SetEngineThrust("1", 0.25);
        SetEngineThrust("2", 0.25);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::A)) {
        SetEngineThrustAngle("1", 0);
        SetEngineThrustAngle("2", 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A)) {
        SetEngineThrustAngle("1", 1);
        SetEngineThrustAngle("2", 1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::D)) {
        SetEngineThrustAngle("1", -1);
        SetEngineThrustAngle("2", -1);
    }
    else {
        SetEngineThrustAngle("1", 0);
        SetEngineThrustAngle("2", 0);
    }
}

