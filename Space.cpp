#include "Space.h"

Space::Space(const String& f, const Vector2f& pos) : file(f), start_pos(pos) {
	image.loadFromFile("images/" + f);
	texture.loadFromImage(image);
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(rand() % 1000, rand() % 1000, 3 * window_x(), 3 * window_y()));

	bodies.push_back(Object{ "Venera.png", {0,0}, 152, 152, 0 });
	float x = (rand() % 10 / 10.0 - 0.5) * window_x();
	float y = -(rand() % 10 / 20.0) * window_y();
	positions.push_back({ x,y });
}
void Space::Update(const View& view) {
	float x = view.getCenter().x - 1.5*window_x() - view.getCenter().x / 100;
	float y = view.getCenter().y - 1.5*window_y() - view.getCenter().y / 100;
	sprite.setPosition(x, y);

	x = positions[0].x + view.getCenter().x + (start_pos.x +-view.getCenter().x) / 50;
	y = positions[0].y + view.getCenter().y + (start_pos.y - view.getCenter().y) / 50;
	bodies[0].SetPosition({x,y}, 0);
}
void Space::Draw(RenderWindow& window) const {
	window.draw(sprite);

	for (const auto& b : bodies) {
		b.Draw(window);
	}
}
