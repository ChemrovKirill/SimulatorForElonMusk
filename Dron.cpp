#include "Dron.h"

Dron::Dron(sf::Vector2f position) : Ship("Dron.png", download(position)) {
	assembly();
}
RigidBodyParameters Dron::download(sf::Vector2f position) {
	std::ifstream fin("data/Dron.txt");
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


void Dron::assembly() {
	AddEngine(Engine(Object("fire.png", Vector2f(10, 10), 0), Vector2f(0.5, 1),
		Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "1");
	AddEngine(Engine(Object("fireleft.png", Vector2f(0, 0),0), Vector2f(0.22, 0.87),
		Force(false, 100, Vector2f(-0.5, -1), Vector2f(0, 0.5)), 10), "2");
	AddEngine(Engine(Object("fireright.png", Vector2f(0, 0), 0), Vector2f(0.78, 0.87),
		Force(false, 100, Vector2f(0.5, -0.5), Vector2f(1, 0.5)), 10), "3");
}
void Dron::control() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		EngineOn("1");
	}
	else {
		EngineOff("1");
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		EngineOn("2");
	}
	else {
		EngineOff("2");
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		EngineOn("3");
	}
	else {
		EngineOff("3");
	}
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		SetEngineThrust("1", 0.5);
	}
	
	else if (Keyboard::isKeyPressed(Keyboard::LControl)) {
		SetEngineThrust("1", 2);
	}
	else {
		SetEngineThrust("1", 1);
	}
}
