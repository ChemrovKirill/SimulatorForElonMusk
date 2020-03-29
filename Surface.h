#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
#include "Object.h"

using namespace sf;

size_t screen_x();
size_t screen_y();

size_t window_x();
size_t window_y();

class Surface {
protected:
	VertexArray surface;
	std::vector<VertexArray> lakes;
	Vector2f center_position;
	Vector2f left_position;
	float x_spacing;
	int pixel_size;
	int vertex_count;
	int down_board = 5 * window_y();
	int up_board = -3 * window_y();
	int iter_0; //surface[iter_0].position.x = 0 (.y = down_board)
	Texture texture;
	String file;
	Image image;
public:
	Surface(const String& file, const float& spacing);
	void SetTexture();
	float YtoX(const float&);
	void GenerateSlope(Vector2f& point, const int& x_boarder, const size_t& rough, const float& angle);
	void Generate(const size_t& rough);
	void Update(const float& dt);
	void Draw(RenderWindow&) const;
	int Get_iter_0() const;
	float Get_spacing() const;
	void GenerateLake(Vector2f& point, const int& x_boarder, const size_t& rough);
	size_t Get_VertexCount() const;
	Vertex GetVertex(const int& i) const;
};