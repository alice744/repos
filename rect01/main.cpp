#include <stdio.h>
#include <conio.h>
#include "rectangle.h"
#include <windowsx.h>
#include <windows.h>
#include<locale.h>

void main() {
	setlocale(LC_ALL, "RUS");
	FILE*fin;
	fopen_s(&fin, "test.txt", "rt");
	Point rectangle_points[4];
	int type;
	fscanf_s(fin, "%d", &type);
	for (int i = 0; i < 4; i++) {
		fscanf_s(fin, "%lf%lf", &rectangle_points[i].x, &rectangle_points[i].y);
	}
	Rectangle * rectangle;
	try {
		rectangle = new Rectangle(rectangle_points);
	}
	catch (exceptions error) {
		switch (error) {
		case RectangleError:
			printf_s("‘игура не €вл€етс€ пр€моугольником.");
			_getch();
			return;
		case fildError:
			printf_s("ƒиапазон координат превышен.");
			_getch();
			return;
		default:
			break;
		}
	}
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hHoldPen = SelectPen(hdc, hRedPen);
	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hHoldBrush = SelectBrush(hdc, hGreenBrush);
	SetBkColor(hdc, RGB(0, 0, 0));
	switch (type) {
	case 1:
		do {
			GetClientRect(hwnd, &rt);
			rectangle->ContourDraw(hdc, rt);
		} while (_getch() != 27);
		break;
	case 2:
		do {
			GetClientRect(hwnd, &rt);
			rectangle->ColourDraw(hdc, rt, RGB(255, 0, 0));
		} while (_getch() != 27);
		break;
	case 3:
		for (int i = 0; i < 4; i++) {
			fscanf_s(fin, "%lf%lf", &rectangle_points[i].x, &rectangle_points[i].y);
		}
		Rectangle * voidzone;
		try {
			voidzone = new Rectangle(rectangle_points);
		}
		catch (exceptions error) {
			printf_s("¬нутренн€€ фигура не €вл€етс€ пр€моугольником\n");
			_getch();
			return;
		}
		do {
			GetClientRect(hwnd, &rt);
			try {
				rectangle->VoidDraw(hdc, rt, *voidzone, RGB(255, 0, 0));
			}
			catch (exceptions error) {
				printf_s("¬нутренн€€ фигура выходит за границы\n");
				_getch();
				return;
			}
		} while (_getch() != 27);
		delete voidzone;
		break;
	}

	SelectPen(hdc, hHoldPen);
	SelectBrush(hdc, hHoldBrush);
	DeletePen(hRedPen);
	DeleteBrush(hGreenBrush);
	ReleaseDC(hwnd, hdc);
	delete rectangle;
	fclose(fin);
	_getch();
	system("cls");
}