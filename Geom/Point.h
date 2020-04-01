#pragma once

struct Point {
	double x;
	double y;

	Point() : x(0), y(0){}
	Point(double new_x, double new_y) : x(new_x), y(new_y) {}
	Point(const Point& p) { x = p.x; y = p.y; }

	Point operator = (Point r) { x = r.x; y = r.y; return r; }

	bool operator ==(Point p) const { return ((x == p.x) && (y == p.y)); }
	bool operator !=(Point p) const { return !((x == p.x) && (y == p.y)); }

	void Print() const  {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		SetPixel(hdc, x, y, RGB(255, 255, 255));
		SetPixel(hdc, x + 1, y + 1, RGB(255, 255, 255));
		SetPixel(hdc, x - 1, y + 1, RGB(255, 255, 255));
		SetPixel(hdc, x + 1, y - 1, RGB(255, 255, 255));
		SetPixel(hdc, x - 1, y - 1, RGB(255, 255, 255));
	}
};

