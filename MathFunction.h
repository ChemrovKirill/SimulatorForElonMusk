#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Geom/Geometric.h"

#define PI 3.1415f
#define RAD (PI / 180.f)

sf::Vector2f operator + (const sf::Vector2f& vl, const sf::Vector2f& vr);
sf::Vector2f operator - (const sf::Vector2f& vl, const sf::Vector2f& vr);
sf::Vector2f operator * (const sf::Vector2f& vl, float x);
sf::Vector2f operator / (const sf::Vector2f& vl, float x);

std::ostream& operator<<(std::ostream& out ,const sf::Vector2f& v);

float sqal_mult(const sf::Vector2f& vl , const sf::Vector2f& v2);
float vect_mult(const sf::Vector2f& vl , const sf::Vector2f& v2);

float sqal(const sf::Vector2f& v);

const sf::Vector2f rotate_to_angle(const sf::Vector2f& v, float a);
float angle_between_2_vectors(const sf::Vector2f& vl, const sf::Vector2f& v2);

sf::Vector2f normal_to_line(const Line& l);