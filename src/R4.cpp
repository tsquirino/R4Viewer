#include "R4.h"
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>

R4::R4()
{
	theta[0] = 0;
	theta[1] = 0;
	theta[2] = 0;
	theta[3] = 0;
	theta[4] = 0;
	theta[5] = 0;
}

void R4::def_angulos(float theta1, float theta2, float theta3, float theta4, float theta5, float theta6)
{
	theta[0] = theta1 * M_PI / 180;
	theta[1] = theta2 * M_PI / 180;
	theta[2] = theta3 * M_PI / 180;
	theta[3] = theta4 * M_PI / 180;
	theta[4] = theta5 * M_PI / 180;
	theta[5] = theta6 * M_PI / 180;
}

void R4::rotacao(int angulo, float& x, float& y, float& z, float& w)
{
	float x_, y_, z_, w_;
	switch (angulo)
	{
	case 1:
		x_ = cos(theta[0]) * x - sin(theta[0]) * y;
		y_ = sin(theta[0]) * x + cos(theta[0]) * y;
		z_ = z;
		w_ = w;
		break;
	case 2:
		x_ = x;
		y_ = cos(theta[1]) * y - sin(theta[1]) * z;
		z_ = sin(theta[1]) * y + cos(theta[1]) * z;
		w_ = w;
		break;
	case 3:
		x_ = x;
		y_ = y;
		z_ = cos(theta[2]) * z - sin(theta[2]) * w;
		w_ = sin(theta[2]) * z + cos(theta[2]) * w;
		break;
	case 4:
		x_ = cos(theta[3]) * x - sin(theta[3]) * y;
		y_ = sin(theta[3]) * x + cos(theta[3]) * y;
		z_ = z;
		w_ = w;
		break;
	case 5:
		x_ = x;
		y_ = cos(theta[4]) * y - sin(theta[4]) * z;
		z_ = sin(theta[4]) * y + cos(theta[4]) * z;
		w_ = w;
		break;
	case 6:
		x_ = cos(theta[5]) * x - sin(theta[5]) * y;
		y_ = sin(theta[5]) * x + cos(theta[5]) * y;
		z_ = z;
		w_ = w;
		break;
	default:
		break;
	}
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

void R4::vertice(float x, float y, float z, float w)
{
	// Obtém posição rotacionada do vértice
	float x_ = x;
	float y_ = y;
	float z_ = z;
	float w_ = w;
	for (int i = 1; i <= 6; i++)
		rotacao(i, x_, y_, z_, w_);

	// Projeta vértice do R4 no R3 (projeção ortogonal paralela)
	glVertex2f(x_, y_);
}