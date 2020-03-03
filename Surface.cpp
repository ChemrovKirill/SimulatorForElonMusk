#include "Surface.h"

using namespace sf;

Surface::Surface() {
	vertex_count = size_t(pixel_size / x_spacing);
	surface.setPrimitiveType(TriangleStrip);
	image.loadFromFile("images/" + file);
	texture.loadFromImage(image);
	Vector2f point = center_position;
	srand(time(NULL));
	float slope_direction;
	for (int i = 0; i <= 2*vertex_count; ++i) {
		/*switch (rand() % 4) 
		{
		case 0 :
			surface.append(Vertex(point, Color::Yellow));
			break;
		case 1:
			surface.append(Vertex(point, Color::Red));
			break;
		case 2:
			surface.append(Vertex(point, Color::Blue));
			break;
		case 3:
			surface.append(Vertex(point, Color::Green));
			break;
		}*/
		surface.append(Vertex(point, Color::White));
		surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), 700 - point.y);
		surface.append(Vertex(Vector2f(point.x, 700), Color::Red));
		++i;
		surface[i].texCoords = Vector2f(x_spacing * ((i / 2) % 2), 0);
		slope_direction = ((float)(rand() % 100)) / 100 - 0.5f;
		point.x += x_spacing;
		point.y += (float)(rand() % 30) * slope_direction;
	}
}

void Surface::Draw(RenderWindow& window) const {
	window.draw(surface, &texture);
}