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

enum class Hole {
	EMPTY,
	LAKE,
	ICE,
};

class Surface {
protected:
	VertexArray surface;
	std::vector<VertexArray> lakes;
	std::vector<VertexArray> snow;
	std::vector<VertexArray> glaciers;
	Vector2f left_position;
	float x_spacing;
	int pixel_size;
	int vertex_count;
	int down_board = 5 * window_y();
	int up_board = -3 * window_y();
	int iter_0; //surface[iter_0].position.x = 0 (.y = down_board)
	Texture texture;
	Texture ice_texture;
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
	void GenerateHole(Vector2f& point, const int& x_boarder, size_t rough, Hole);
	void GenerateSnow(const int& coverage);
	size_t Get_VertexCount() const;
	Vertex GetVertex(const int& i) const;
};