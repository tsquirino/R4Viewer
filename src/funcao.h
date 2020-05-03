#ifndef FUNCAO_H
#define FUNCAO_H

#include "R4.h"
#define _USE_MATH_DEFINES
#include <cmath>

class funcao
{
private:
	float rmin, rmax, tmin, tmax;
	int pontos, ID;
public:
	funcao(int funcID = 1, int n = 10, float rm = -1, float rM = 1, float tm = 0, float tM = 2 * M_PI);
	void f(float x, float y, float& z, float& w);
	void plot_f(R4 r);
	char* f_expr();
};

#endif