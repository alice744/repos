#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include <stdio.h>
#include <windowsx.h>
#include <Windows.h>
#include <math.h>
#include <cfloat>
class Point {
public:
	double x;
	double y;
};
enum exceptions { RectangleError, fildError, voidZoneError };
class Rectangle
{
public:
	Point * get_Coords();
	Rectangle(Point * points);
	void ContourDraw(HDC hdc, RECT rt);
	void ColourDraw(HDC hdc, RECT rt, COLOR16 color);
	void VoidDraw(HDC hdc, RECT rt, Rectangle VoidZone, COLOR16 color);
private:
	bool isrectangle();
	bool rectangleInScreen();
	bool DotInRange(Point A);
	void set_Coords(Point coords[4]);
	Point A;
	Point B;
	Point C;
	Point D;
};
#endif