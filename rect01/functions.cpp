#include"functions.h"
#include <math.h>

double GetVectorLength(Point A, Point B) {
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}
double Rectangle_square(Point A, Point B, Point C, Point D) {
	double AB = GetVectorLength(A, B);
	double BC = GetVectorLength(B, C);
	//double CD = GetVectorLength(C, D);
	//double AD = GetVectorLength(A, D);
	return AB * BC;

}