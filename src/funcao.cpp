#include "funcao.h"
#include "R4.h"
#include <GL/glut.h>
#include <cmath>

funcao::funcao(int funcID, int n, float rm, float rM, float tm, float tM)
{
	ID = funcID;
	pontos = n;
	rmin = rm;
	rmax = rM;
	tmin = tm;
	tmax = tM;
}

void funcao::f(float x, float y, float& z, float& w)
{
	switch (ID)
	{
	case 2:
		z = 1;
		w = 1;
		break;
	case 3:
		z = exp(x) * cos(y);
		w = exp(x) * sin(y);
		break;
	case 4:
		z = sin(x) * cosh(y);
		w = cos(x) * sinh(y);
		break;
	case 1:
	default:
		z = x * x - y * y;
		w = 2 * x * y;
		break;
	}
}

char* funcao::f_expr()
{
	switch (ID)
	{
	case 2:
		return "f(Z) = 1 + i";
	case 3:
		return "f(Z) = exp(Z)";
	case 4:
		return "f(Z) = sen(Z)";
	case 1:
	default:
		return "f(Z) = Z^2";
	}
}

void funcao::plot_f(R4 amb)
{
	float r, t;
	float dr = (rmax - rmin) / pontos;
	float dt = (tmax - tmin) / pontos;
	r = rmin;
	for (int i = 0; i < pontos; i++)
	{
		t = tmin;
		for (int j = 0; j < pontos; j++)
		{
			float z, w;
			glBegin(GL_LINE_LOOP);
			f(r * cos(t), r * sin(t), z, w);
			amb.vertice(r * cos(t), r * sin(t), z, w);
			f((r + dr) * cos(t), (r + dr) * sin(t), z, w);
			amb.vertice((r + dr) * cos(t), (r + dr) * sin(t), z, w);
			f((r + dr) * cos(t + dt), (r + dr) * sin(t + dt), z, w);
			amb.vertice((r + dr) * cos(t + dt), (r + dr) * sin(t + dt), z, w);
			f(r * cos(t + dt), r * sin(t + dt), z, w);
			amb.vertice(r * cos(t + dt), r * sin(t + dt), z, w);
			glEnd();
			t += dt;
		}
		r += dr;
	}
}