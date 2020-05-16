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
	METEORITE
};

class Surface {
protected:
	VertexArray surface;
	std::vector<VertexArray> lakes;
	std::vector<VertexArray> snow;
	std::vector<VertexArray> glaciers;
	std::vector<VertexArray> meteorites;
	std::map<float, float> planes;
	Vector2f left_position;
	int pixel_size;
	int vertex_count;
	int iter_0; //surface[iter_0].position.x = 0 (.y = down_border)

	float x_spacing = 20; //space between vertexes
	int step = 500; //generation step
	int down_border = 5 * window_y();
	int up_border = -5 * window_y();
	int max_angle; //0-70
	int rough; //0-10...
	int snow_coverage; //0-100 %
	std::map<Hole, int> probability;
	int air_density;
	int gravity;

	Color surface_color;
	Color meteorites_color;
	Color lakes_color;

	Texture texture;
	Texture ice_texture;
	Texture meteorite_texture;
	String file;
	Image image;
public:
	Surface(const String&, const int& rough, const int& snow_coverage, std::map<Hole, int>, int _max_angle, int gravity, int air_d);
	void SetTexture();
	
	size_t Get_VertexCount() const;
	Vertex GetVertex(const int& i) const;
	int Get_iter_0() const;
	float Get_spacing() const;
	float YtoX(const float&);
	int GetGravity() const;
	int GetAirDensity() const;

	void Generate();
	void ColorGenerate();
	void GenerateSlope(Vector2f& point, const int& x_border, const int& loc_rough, const float& angle);
	void GenerateHole(Vector2f& point, const int& x_border, Hole);
	void Generate_V(Vector2f& point, const float& step, const int& step_count, const int& loc_rough);
	void Generate_U(Vector2f& point, const float& step, const int& step_count, const int& loc_rough);
	void GenerateSnow();

	void Update(const float& dt);
	void Draw(RenderWindow&) const;
};

void mix(std::vector<int>& v);