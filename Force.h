#pragma once
#include <SFML/Graphics.hpp>

struct Force {
	bool exist;
	bool is_force_field;

	float force;
	sf::Vector2f force_vector; //if the force creates a field, then the vector is the field strength, otherwise
						   //unit vector directed relative to the orientation of the box: 
						   //(0,-1) - up relative to the nose, (0,1) - down, (1,0) - right, (-1,0) - left
	sf::Vector2f force_point;  //the point of application of force, takes values from 0 to 1

	Force();
	Force(bool field, float new_force, sf::Vector2f start_vector, sf::Vector2f start_force_point);
	Force(const Force& f);
	Force operator = (const Force&);
};