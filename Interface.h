#pragma once
#include "ship.h"
#include<string.h>
class Interface  {
private:
	Font font;
		
	float height ;
	Text text_height{ "", font, 10 };
	float angle;
	Text text_angle{ "", font, 10 };
	float angular_velocity;
	Text text_angular_velocity{ "", font, 10 };
	float velocity_X;
	Text text_velocity_X{ "", font, 10 };
	float velocity_Y;
	Text text_velocity_Y{ "", font, 10 };
	float fuel;
	Text text_fuel{ "", font, 10 };
	float Coordinate_X;
	Text Position{ "", font, 10 };
	String status;
	Text text_status{ "", font, 20 };
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