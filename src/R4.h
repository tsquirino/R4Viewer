#ifndef R4_H
#define R4_H

class R4
{
private:
	float theta[6];
	void rotacao(int angulo, float& x, float& y, float& z, float& w);
public:
	R4();
	void def_angulos(float theta1, float theta2, float theta3, float theta4, float theta5, float theta6);
	void vertice(float x, float y, float z, float w);
};

#endif