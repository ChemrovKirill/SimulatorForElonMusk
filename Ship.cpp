#include "Ship.h"
#include <iostream>

Ship::Ship(const RigidBody& rb, std::map<std::string, Engine>& _engines)
	: RigidBody(rb) {
	for (auto& e : _engines) {
		AddForce(e.second.GetForce(), e.first);
		e.second.SetPosition(Vector2f(position.x + width * e.second.GetRelPos().x - e.second.GetWidth() / 2,
			position.y + height * e.second.GetRelPos().y - e.second.GetHeight() / 2), angle);
		engines[e.first] = e.second;
	}
}

void Ship::Draw(RenderWindow& window) const {
	Object::Draw(window);
	for (const auto& e : engines) {
		e.second.Draw(window);
	}
}

void Ship::Control() {
	if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
		engines["left"].SetOn();
	}
	else {
		engines["left"].SetOff();
	}

	if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
		engines["right"].SetOn();
	}
	else {
		engines["right"].SetOff();
	}
}

void Ship::UpdatePosition(const float& dt) {
	for (auto& e : engines) {
		e.second.SetPosition(Vector2f(position.x + width * e.second.GetRelPos().x - e.second.GetWidth() / 2,
			position.y + height * e.second.GetRelPos().y - e.second.GetHeight() / 2), angle);
		forces[e.first] = e.second.GetForce();
	}
	RigidBody::UpdatePosition(dt);
}