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
	EMPTY_U,
	EMPTY_V,
	LAKE,
	ICE,
	METEORITE,
};

class Surface {
protected:
	VertexArray surface;
	std::vector<VertexArray> lakes;
	std::vector<VertexArray> snow;
	std::vector<VertexArray> glaciers;
	std::vector<VertexArray> meteorites;

	Vector2f left_position;
	float x_spacing;
	int pixel_size;
	int vertex_count;
	int down_board = 5 * window_y();
	int up_board = -3 * window_y();
	int iter_0; //surface[iter_0].position.x = 0 (.y = down_board)
	Texture texture;
	Texture ice_texture;
	Texture meteorite_texture;
	String file;
	Image image;
public:
	Surface(const String& file, const float& spacing);
	void SetTexture();
	
	size_t Get_VertexCount() const;
	Vertex GetVertex(const int& i) const;
	int Get_iter_0() const;
	float Get_spacing() const;
	float YtoX(const float&);

	void Generate(const size_t& rough);
	void GenerateSlope(Vector2f& point, const int& x_boarder, const size_t& rough, const float& angle);
	void GenerateHole(Vector2f& point, const int& x_boarder, size_t rough, Hole);
	void Generate_V(Vector2f& point, const float& step, const int& step_count, size_t rough);
	void Generate_U(Vector2f& point, const float& step, const int& step_count, size_t rough);
	void GenerateSnow(const int& coverage);

	void Update(const float& dt);
	void Draw(RenderWindow&) const;
};