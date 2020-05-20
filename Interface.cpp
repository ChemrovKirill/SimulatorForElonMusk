#include "Interface.h"
#include<sstream>

Interface::Interface(const float& h, const float& a, const float& A_V, const float& V_X, const float& V_Y, const float& f, const float& x, const String& new_status) : height(h),
angle(a), angular_velocity(A_V), velocity_X(V_X), velocity_Y(V_Y), fuel(f), Coordinate_X(x), status(new_status) {
	font.loadFromFile("fonts/FRAHV.ttf");
}
void Interface::SetHeight(const float& h) {
	height = h;
}
void Interface::SetAngle(const float& a) {
	angle = a;
}
void Interface::SetAngVelocity(const float& AngVel) {
	angular_velocity = AngVel;
}
void Interface::SetVelocityX(const float& VelX) {
	velocity_X = VelX;
}
void Interface::SetVelocityY(const float& VelY) {
	velocity_Y = VelY;
}
void Interface::SetFuel(const float& f) {
	fuel = f;
}
void Interface::SetCoordinate_X(const float& x) {
	Coordinate_X = x;
}
void Interface::SetStatus(const String& s) {
	status = s;
}
void Interface::Draw(RenderWindow& window, const View& v) {
	std::ostringstream s_height;
	s_height << "Height: " << height;
	text_height.setString(s_height.str());
	text_height.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2);
	if (height < 3000) {
		text_height.setFillColor(Color::Green);
	}
	else {
		text_height.setFillColor(Color::Red);
	}
	window.draw(text_height);
	std::ostringstream s_angle;
	s_angle << "Angle: " << angle;
	text_angle.setString(s_angle.str());
	text_angle.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 15);
	text_angle.setFillColor(Color::Blue);
	window.draw(text_angle);
	std::ostringstream s_angular_velocity;
	s_angular_velocity << "Angular_velocity: " << angular_velocity;
	text_angular_velocity.setString(s_angular_velocity.str());
	text_angular_velocity.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 30);
	if (angular_velocity < 150) {
		text_angular_velocity.setFillColor(Color::Green);
	}
	else if (angular_velocity > 150 && angular_velocity < 300) {
		text_angular_velocity.setFillColor(Color::Yellow);
	}
	else {
		text_angular_velocity.setFillColor(Color::Red);
	}
	window.draw(text_angular_velocity);
	std::ostringstream s_velocity_X;
	s_velocity_X << "velocity_X: " << velocity_X;
	text_velocity_X.setString(s_velocity_X.str());
	text_velocity_X.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 45);
	if (abs(velocity_X) < 1500) {
		text_velocity_X.setFillColor(Color::Green);
	}
	else if (abs(velocity_X) > 1500 && abs(velocity_X) < 3500) {
		text_velocity_X.setFillColor(Color::Yellow);
	}
	else {
		text_velocity_X.setFillColor(Color::Red);
	}
	window.draw(text_velocity_X);
	std::ostringstream s_velocity_Y;
	s_velocity_Y << "velocity_Y: " << -velocity_Y;
	text_velocity_Y.setString(s_velocity_Y.str());
	text_velocity_Y.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 60);
	if (abs(velocity_Y) < 1500) {
		text_velocity_Y.setFillColor(Color::Green);
	}
	else if (abs(velocity_Y) > 1500 && abs(velocity_Y) < 3500) {
		text_velocity_Y.setFillColor(Color::Yellow);
	}
	else {
		text_velocity_Y.setFillColor(Color::Red);
	}
	window.draw(text_velocity_Y);
	std::ostringstream s_fuel;
	s_fuel << "fuel: " << fuel << "/10";

	text_fuel.setString(s_fuel.str());
	text_fuel.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 75);
	if (fuel > 6) {
		text_fuel.setFillColor(Color::Green);
	}
	else if (fuel > 3) {
		text_fuel.setFillColor(Color::Yellow);
	}
	else {
		text_fuel.setFillColor(Color::Red);
	}
	window.draw(text_fuel);
	std::ostringstream s_Position;
	s_Position << "Coordinate: (" << Coordinate_X << "," << height << ")";
	Position.setString(s_Position.str());
	Position.setPosition(v.getCenter().x - window_x() / 2, v.getCenter().y - window_y() / 2 + 90);
	Position.setFillColor(Color::Blue);
	window.draw(Position);
	
	text_status.setString(status);
	text_status.setPosition(v.getCenter().x - text_status.getLocalBounds().width/2 , v.getCenter().y - window_y() / 2 + 90);
	text_status.setFillColor(Color::Blue);
	text_status.setStyle(sf::Text::Bold);
	if (status == "You are in flight") {
		text_status.setFillColor(Color::Green);
	}
	else if (status == "Landing succesfull!") {
		text_status.setFillColor(Color::Green);
	}
	else {
		text_status.setFillColor(Color::Red);
	}
	window.draw(text_status);

}