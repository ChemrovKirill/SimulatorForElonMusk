#pragma once
#include "ship.h"
#include<string.h>
class Interface  {
private:
	Font font;
	int gap = 20;

	float height ;
	Text text_height{ "", font, 20 };
	float angle;
	Text text_angle{ "", font, 20 };
	float angular_velocity;
	Text text_angular_velocity{ "", font, 20 };
	float velocity_X;
	Text text_velocity_X{ "", font, 20 };
	float velocity_Y;
	Text text_velocity_Y{ "", font, 20 };
	float fuel;
	Text text_fuel{ "", font, 20 };
	float Coordinate_X;
	Text Position{ "", font, 20 };
	String status;
	Text text_status{ "", font, 40 };
public:
	Interface(const float& h, const float& a, const float& A_V, const float& V_X, const float& V_Y, const float& f, const float& X, const String& new_status);
	void SetHeight(const float& h) ;
	void SetAngle(const float& a);
	void SetAngVelocity(const float& AngVel) ;
	void SetVelocityX(const float& VelX) ;
	void SetVelocityY(const float& VelY) ;
	void SetFuel(const float& f);
	void SetCoordinate_X(const float& x);
	void SetStatus(const String& s);
	void Draw(RenderWindow& window, const View& v);

};