#include "SuperPuperShip.h"

SuperPuperShip::SuperPuperShip(sf::Vector2f position) : Ship("SuperPuperShip.png", download(position)) {
	assembly();
}
RigidBodyParameters SuperPuperShip::download(sf::Vector2f position) {
	std::ifstream fin("data/SuperPuperShip.txt");
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


void SuperPuperShip::assembly() {
	AddEngine(Engine(Object("fire.png", Vector2f(10, 10), 0), Vector2f(0.5, 1),
		Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "1");
	AddEngine(Engine(Object("bluefire.png", Vector2f(10, 10), 0), Vector2f(0.5, 1),
		Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "6");
	AddEngine(Engine(Object("fire.png", Vector2f(10, 10), 0), Vector2f(0.25, 0.69),
		Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "4");
	AddEngine(Engine(Object("fire.png", Vector2f(10, 10), 0), Vector2f(0.75, 0.69),
		Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "5");
	AddEngine(Engine(Object("fireleft.png", Vector2f(0, 0), 0), Vector2f(0.22, 0.83),
		Force(false, 100, Vector2f(-0.5, -1), Vector2f(0, 0.5)), 10), "2");
	AddEngine(Engine(Object("fireright.png", Vector2f(0, 0), 0), Vector2f(0.78, 0.83),
		Force(false, 100, Vector2f(0.5, -1), Vector2f(1, 0.5)), 10), "3");
}
void SuperPuperShip::control() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			EngineOff("1");
			EngineOn("6");
		}
		else{ 
			EngineOn("1");
			EngineOff("6");
		}
	}
	else {
		EngineOff("1");
		EngineOff("6");
		
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
		SetEngineThrust("6", 0.5);
	}

	else if (Keyboard::isKeyPressed(Keyboard::LControl)) {
		SetEngineThrust("1", 2);
		EngineOn("4");
		EngineOn("5");
	}
	else {
		SetEngineThrust("1", 1);
		EngineOff("4");
		EngineOff("5");
	}
}

void SuperPuperShip::DrawShip(RenderWindow & window) const {
	Draw(window);
	for (const auto& e : engines) {
		if (e.second.If_on()) {
			e.second.Draw(window);
		}
	}
}
