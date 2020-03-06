#include "Ship.h"

Ship::Ship(const RigidBody& rb, std::map<std::string, Engine>& _engines)
	: RigidBody(rb) {
	for (auto& e : _engines) {
		AddForce(e.second.GetForce(), e.first);
		e.second.SetPosition(Vector2f(position.x + width * e.second.GetRelPos().x - e.second.GetWidth() / 2,
			position.y + height * e.second.GetRelPos().y - e.second.GetHeight() / 2), 0);
		engines[e.first] = e.second;
	}
}

void Ship::Draw(RenderWindow& window) const {
	Object::Draw(window);
	for (const auto& e : engines) {
		e.second.Draw(window);
	}
}