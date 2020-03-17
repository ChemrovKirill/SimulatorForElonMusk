#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
#include "RigidBody.h"

using namespace sf;

size_t screen_x();
size_t screen_y();
size_t window_x();
size_t window_y();

class Surface {
protected:
	VertexArray surface;
	Vector2f center_position;
	Vector2f left_position;
	float x_spacing;
	int pixel_size;
	int vertex_count;
	int down_board = 5 * window_y();
	int up_board = -3 * window_y();
	int iter_0;
	Texture texture;
	String file = "surface.png";
	Image image;
public:
	Surface(const String& file, const float& spacing);
	void SetTexture();
	void GenerateSlope(Vector2f& point, const int& x_boarder, const size_t& rough, const float& angle);
	void Generate(const size_t& rough);
	void Draw(RenderWindow&) const;
};