#include "MathFunction.h"
#include "iostream"

sf::Vector2f operator + (const sf::Vector2f& vl, const sf::Vector2f& vr) {
	return sf::Vector2f(vl.x + vr.x, vl.y + vr.y);
}
sf::Vector2f operator - (const sf::Vector2f& vl, const sf::Vector2f& vr) {
	return sf::Vector2f(vl.x - vr.x, vl.y - vr.y);
}
sf::Vector2f operator * (const sf::Vector2f& vl, float x) {
	return sf::Vector2f(vl.x * x, vl.y * x);
}
sf::Vector2f operator / (const sf::Vector2f& vl, float x) {
	return sf::Vector2f(vl.x / x, vl.y / x);
}

std::ostream& operator<<(std::ostream& out, const sf::Vector2f& v) {
	out << "(" << v.x << "/" << v.y << ")";
	return out;
}

float sqal_mult(const sf::Vector2f& vl, const sf::Vector2f& vr) {
	return vl.x * vr.x + vl.y * vr.y;
}
float vect_mult(const sf::Vector2f& vl, const sf::Vector2f& vr) {
	return sin(angle_between_2_vectors(vl, vr) * sqal(vl) * sqal(vr));
}

float sqal(const sf::Vector2f& v) {
	return sqrt(sqal_mult(v, v));
}

const sf::Vector2f rotate_to_angle(const sf::Vector2f& v, float a) {
	return sf::Vector2f(v.x * cos(a) - v.y * sin(a), v.x * sin(a) + v.y * cos(a));
}
float angle_between_2_vectors(const sf::Vector2f& vl, const sf::Vector2f& vr) {
	sf::Vector2f vnl = vl / sqal(vl), vnr = vr / sqal(vr);
	float a = acos(vnl.x), b = acos(vnr.x);
	if (vnl.y < 0) { a *= -1; }
	if (vnr.y < 0) { b *= -1; }

	float x = b - a;
	return x;
}

sf::Vector2f normal_to_line(const Line& l) {
	sf::Vector2f v(l.GetK(), -1);
	return v / sqal(v);
}