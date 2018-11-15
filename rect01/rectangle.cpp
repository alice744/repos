#include "rectangle.h"
#include "functions.h"

Point * Rectangle::get_Coords() {
	Point points[4];
	points[0] = A;
	points[1] = B;
	points[2] = C;
	points[3] = D;
	return points;
}

bool Rectangle::rectangleInScreen() {
	Point * points = get_Coords();
	for (int i = 0; i < 4; i++) {
		if (!(points[i].x >= 0 && points[i].x <= 10 && points[i].y >= 0 && points[i].y <= 10))
			return 0;
	}
	return 1;
}

void Rectangle::set_Coords(Point points[4]) {
	A = points[0];
	B = points[1];
	C = points[2];
	D = points[3];
}
Rectangle::Rectangle(Point * points) {
	A = points[0];
	B = points[1];
	C = points[2];
	D = points[3];
	if (!isrectangle()) {
		throw RectangleError;
	}
	if (!rectangleInScreen()) {
		throw fildError;
	}
}

bool Rectangle::isrectangle() { //проверка на прямоугольник
	if (1) {
		return 1;
	}
	return 0;
}

bool Rectangle::DotInRange(Point Dot) {
	double boolean = Rectangle_square(A, B, Dot) + Rectangle_square(B, C, Dot) +
		Rectangle_square(C, D, Dot) + Rectangle_square(A, D, Dot) - Rectangle_square(A, B, C, D);
	if (boolean <= FLT_EPSILON) {
		return 1;
	}
	return 0;
}

void Rectangle::ContourDraw(HDC hdc, RECT rt) {
	MoveToEx(hdc, A.x / 10 * rt.right, A.y / 10 * rt.bottom, NULL);
	LineTo(hdc, B.x / 10 * rt.right, B.y / 10 * rt.bottom);
	LineTo(hdc, C.x / 10 * rt.right, C.y / 10 * rt.bottom);
	LineTo(hdc, D.x / 10 * rt.right, D.y / 10 * rt.bottom);
	LineTo(hdc, A.x / 10 * rt.right, A.y / 10 * rt.bottom);
}

void Rectangle::ColourDraw(HDC hdc, RECT rt, COLOR16 color) {
	ContourDraw(hdc, rt);
	//FloodFill(hdc, get_Center().x / 10 * rt.right, get_Center().y / 10 * rt.bottom, color);
}
void Rectangle::VoidDraw(HDC hdc, RECT rt, Rectangle VoidZone, COLOR16 color) {
	if (DotInRange(VoidZone.A) && DotInRange(VoidZone.B) && DotInRange(VoidZone.C) && DotInRange(VoidZone.D)) {
		ColourDraw(hdc, rt, color);
		HPEN hPenBKColor = CreatePen(PS_SOLID, 1, GetBkColor(hdc));
		HBRUSH hBrushBkColor = CreateSolidBrush(GetBkColor(hdc));
		HPEN hHoldPen = SelectPen(hdc, hPenBKColor);
		HBRUSH hHoldBrush = SelectBrush(hdc, hBrushBkColor);
		VoidZone.ColourDraw(hdc, rt, GetBkColor(hdc));
		SelectPen(hdc, hHoldPen);
		SelectBrush(hdc, hHoldBrush);
		DeletePen(hPenBKColor);
		DeleteBrush(hBrushBkColor);
		return;
	}
	else {
		throw voidZoneError;
	}
}