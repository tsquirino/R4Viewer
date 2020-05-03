#include <GL/glut.h>
#include "funcao.h"					// definir ambiente R4 e plotar fun��o f(Z)
#include <iostream>					// imprimir texto no console
#include <cstdio>					// imprimir valores float com casas decimais limitadas
#include <string>					// manipula��o de strings a serem exibidas na tela
#include <sstream>					// buffer para a montagem das strings
using namespace std;				// biblioteca padr�o do C++, cont�m fun��es e classes utilizadas no programa

// Visualiza��o da fun��o no R4
float theta[6] = { 0, 0, 0, 0, 0, 0 };
R4 r = R4();
funcao f;

// Limites dos eixos
float E = 2;

// Dom�nio da fun��o (forma polar)
float rmin = 0;
float rmax = 1;
float tmin = 0;
float tmax = 2;
int pts = 40;

// Interrup��es - sensibilidade (+/-)
float dtheta = 5;
float dr = 0.05;
float dt = 0.05;
float dE = 0.1;

// Interrup��es - flags
int angulo = 1;
int flag_r = 0;
int flag_t = 0;
bool flag_E = false;
bool flag_n = false;
bool flag_f = false;
int funcID = 1;

// Fun��o para plotar os eixos coordenados x, y, z, w
void eixos()
{
	// Eixo x: vermelho
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	r.vertice(-E, 0, 0, 0);
	r.vertice(E, 0, 0, 0);
	glEnd();

	// Eixo y: verde
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	r.vertice(0, -E, 0, 0);
	r.vertice(0, E, 0, 0);
	glEnd();

	// Eixo z: azul
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	r.vertice(0, 0, -E, 0);
	r.vertice(0, 0, E, 0);
	glEnd();

	// Eixo w: amarelo
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	r.vertice(0, 0, 0, -E);
	r.vertice(0, 0, 0, E);
	glEnd();
}

// Fun��o para mostrar informa��es em formato de texto
void display_text(float x, float y, void* font, char* text)
{
	glRasterPos2f(x, y);
	for (int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font, text[i]);
}

// Fun��o para compor string a ser exibida na tela
char* comp_str(ostream& stream, string& str)
{
	ostringstream& ss = (ostringstream&) stream;
	str = ss.str();
	return (char*)str.c_str();
}

// Fun��o para criar string a partir de um n�mero float, exibindo uma casa decimal
char* float_str(float val, char* buffer)
{
	sprintf(buffer, "%.1f", val);
	return buffer;
}

// Fun��o para organizar e formatar o texto mostrado na tela durante a execu��o do programa
void print_info()
{
	// Vari�veis auxiliar para armazenar/manipular strings a serem mostradas na tela
	string str;
	char buffer[2][20];

	// �ngulos de Euler
	glColor3f(0, 0, 0);
	display_text(-0.96 * E, 0.96 * E, GLUT_BITMAP_HELVETICA_10, "Angulos de Euler (em graus)");
	glColor3f(angulo == 1 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.92 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 1 (xy): " << theta[0], str));
	glColor3f(angulo == 2 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.88 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 2 (yz): " << theta[1], str));
	glColor3f(angulo == 3 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.84 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 3 (zw): " << theta[2], str));
	glColor3f(angulo == 4 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.8 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 4 (xy): " << theta[3], str));
	glColor3f(angulo == 5 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.76 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 5 (yz): " << theta[4], str));
	glColor3f(angulo == 6 ? 1 : 0, 0, 0);
	display_text(-0.96 * E, 0.72 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Angulo 6 (xy): " << theta[5], str));
	glColor3f(0, 0, 0);

	// Fun��o f
	display_text(-0.96 * E, -0.76 * E, GLUT_BITMAP_HELVETICA_10, "Funcao");
	glColor3f(flag_f ? 1 : 0, 0, 0);
	display_text(-0.96 * E, -0.8 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << f.f_expr(), str));
	glColor3f(0, 0, 0);

	// Dom�nio da fun��o f
	display_text(-0.96 * E, -0.86 * E, GLUT_BITMAP_HELVETICA_10, "Dominio da funcao (forma polar)");
	if (flag_r == 0)
	{
		glColor3f(0, 0, 0);
		display_text(-0.96 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(rmin, buffer[0]) << " <= r <= " << float_str(rmax, buffer[1]), str));
	}
	else if (flag_r == 1)
	{
		glColor3f(1, 0, 0);
		display_text(-0.96 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(rmin, buffer[0]) << " <= r", str));
		glColor3f(0, 0, 0);
		display_text(-0.76 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << " <= " << float_str(rmax, buffer[0]), str));
	}
	else
	{
		glColor3f(0, 0, 0);
		display_text(-0.96 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(rmin, buffer[0]) << " <= ", str));
		glColor3f(1, 0, 0);
		display_text(-0.76 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "r <= " << float_str(rmax, buffer[0]), str));
	}
	if (flag_t == 0)
	{
		glColor3f(0, 0, 0);
		display_text(-0.96 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(tmin, buffer[0]) << " pi <= t <= " << float_str(tmax, buffer[1]) << " pi", str));
	}
	else if (flag_t == 1)
	{
		glColor3f(1, 0, 0);
		display_text(-0.96 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(tmin, buffer[0]) << " pi <= t", str));
		glColor3f(0, 0, 0);
		display_text(-0.76 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << " <= " << float_str(tmax, buffer[0]) << " pi", str));
	}
	else
	{
		glColor3f(0, 0, 0);
		display_text(-0.96 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(tmin, buffer[0]) << " pi <= ", str));
		glColor3f(1, 0, 0);
		display_text(-0.76 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "t <= " << float_str(tmax, buffer[0]) << " pi", str));
	}
	glColor3f(0, 0, 0);

	// N�mero de pontos
	display_text(0.2 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Numero de divisoes", str));
	glColor3f(flag_n ? 1 : 0, 0, 0);
	display_text(0.2 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "N = " << pts, str));
	glColor3f(0, 0, 0);

	// Limites dos eixos
	display_text(0.64 * E, -0.78 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << "Eixos", str));
	if (flag_E) glColor3f(1, 0, 0); else glColor3f(1, 0, 0);
	display_text(0.64 * E, -0.82 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(-E, buffer[0]) << " <= x <= " << float_str(E, buffer[1]), str));
	if (flag_E) glColor3f(1, 0, 0); else glColor3f(0, 1, 0);
	display_text(0.64 * E, -0.86 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(-E, buffer[0]) << " <= y <= " << float_str(E, buffer[1]), str));
	if (flag_E) glColor3f(1, 0, 0); else glColor3f(0, 0, 1);
	display_text(0.64 * E, -0.9 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(-E, buffer[0]) << " <= z <= " << float_str(E, buffer[1]), str));
	if (flag_E) glColor3f(1, 0, 0); else glColor3f(0.8, 0.8, 0);
	display_text(0.64 * E, -0.94 * E, GLUT_BITMAP_HELVETICA_10, comp_str(ostringstream() << float_str(-E, buffer[0]) << " <= w <= " << float_str(E, buffer[1]), str));
}

// Fun��o que faz os desenhos na tela
void display()
{
	// Cor de fundo
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Preparar ambiente de visualiza��o
	r.def_angulos(theta[0], theta[1], theta[2], theta[3], theta[4], theta[5]);

	// Plotar eixos
	eixos();

	// Plotar fun��o
	glColor3f(0.75, 0.75, 0.75);
	f = funcao(funcID, pts, rmin, rmax, tmin * M_PI, tmax * M_PI);
	f.plot_f(r);

	// Mostrar na tela informa��es sobre o gr�fico
	print_info();

	// Atualizar buffer
	glutSwapBuffers();
}

// Fun��o que cont�m todas as poss�veis interrup��es via teclado
void keyboard(unsigned char key, int x, int y)
{
	// Identifica��o do comando: tecla pressionada
	switch (key)
	{
	// Comandos prim�rios: selecionar funcionalidade a ser manipulada
	case '1':					// alterar �ngulo 1
		flag_r = 0;
		flag_t = 0;
		angulo = 1;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case '2':					// alterar �ngulo 2
		flag_r = 0;
		flag_t = 0;
		angulo = 2;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case '3':					// alterar �ngulo 3
		flag_r = 0;
		flag_t = 0;
		angulo = 3;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case '4':					// alterar �ngulo 4
		flag_r = 0;
		flag_t = 0;
		angulo = 4;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case '5':					// alterar �ngulo 5
		flag_r = 0;
		flag_t = 0;
		angulo = 5;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case '6':					// alterar �ngulo 6
		flag_r = 0;
		flag_t = 0;
		angulo = 6;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case 'r':					// alterar dom�nio da fun��o: coordenada r
	case 'R':
		angulo = 0;
		flag_t = 0;
		flag_r = 1;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case 't':					// alterar dom�nio da fun��o: coordenada t
	case 'T':
		angulo = 0;
		flag_r = 0;
		flag_t = 1;
		flag_E = false;
		flag_n = false;
		flag_f = false;
		break;
	case 'e':					// alterar limites dos eixos
	case 'E':
		angulo = 0;
		flag_r = 0;
		flag_t = 0;
		flag_E = true;
		flag_n = false;
		flag_f = false;
		break;
	case 'n':					// alterar n�mero de divis�es para o desenho do gr�fico
	case 'N':
		angulo = 0;
		flag_r = 0;
		flag_t = 0;
		flag_E = false;
		flag_n = true;
		flag_f = false;
		break;
	case 'f':					// alterar fun��o f(Z) plotada
	case 'F':
		angulo = 0;
		flag_r = 0;
		flag_t = 0;
		flag_E = false;
		flag_n = false;
		flag_f = true;
		break;

	// Comando secund�rio: alternar entre limite inferior ou superior da funcionalidade selecionada
	case ' ':
		if (flag_r == 1)
			flag_r = 2;
		else if (flag_r == 2)
			flag_r = 1;
		else if (flag_t == 1)
			flag_t = 2;
		else if (flag_t == 2)
			flag_t = 1;
		break;

	// Comandos de regulagem: aumentar ou diminuir valor da funcionalidade selecionada
	case '+':														// +: aumentar
		if (angulo > 0)
			theta[angulo - 1] += dtheta;
		else if (flag_r == 1)
			rmin += dr;
		else if (flag_r == 2)
			rmax += dr;
		else if (flag_t == 1)
			tmin += dt;
		else if (flag_t == 2)
			tmax += dt;
		else if (flag_E)
			E += dE;
		else if (flag_n)
			pts++;
		else if (flag_f)
			funcID++;
		if (rmin >= rmax)
			rmin = rmax - dr;
		if (tmin >= tmax)
			tmin = tmax - dt;
		if (funcID > 4)
			funcID = 1;
		glLoadIdentity();
		gluOrtho2D(-E, E, -E, E);
		break;
	case '-':														// -: diminuir
		if (angulo > 0)
			theta[angulo - 1] -= dtheta;
		else if (flag_r == 1)
			rmin -= dr;
		else if (flag_r == 2)
			rmax -= dr;
		else if (flag_t == 1)
			tmin -= dt;
		else if (flag_t == 2)
			tmax -= dt;
		else if (flag_E)
			E -= dE;
		else if (flag_n)
			pts--;
		else if (flag_f)
			funcID--;
		if (rmin < 0)
			rmin = 0;
		if (rmax <= rmin)
			rmax = rmin + dr;
		if (tmax <= tmin)
			tmax = tmin + dt;
		if (E < dE)
			E = dE;
		if (pts < 5)
			pts = 5;
		if (funcID < 1)
			funcID = 4;
		glLoadIdentity();
		gluOrtho2D(-E, E, -E, E);
		break;

	// Comandos extras: visualizar dom�nio ou imagem da fun��o
	case 'd':								// dom�nio da fun��o (proje��o em xy)
	case 'D':
		theta[0] = 0;
		theta[1] = 0;
		theta[2] = 0;
		theta[3] = 0;
		theta[4] = 0;
		theta[5] = 0;
		break;
	case 'i':								// imagem da fun��o (proje��o em zw)
	case 'I':
		theta[0] = 0;
		theta[1] = 90;
		theta[2] = 90;
		theta[3] = 90;
		theta[4] = 90;
		theta[5] = 0;
		break;

	// Para teclas n�o especificadas, n�o fazer nada
	default:
		return;
	}
	glutPostRedisplay();
}

// Fun��o que mostra as instru��es do programa no console
void console()
{
	cout << "-------- PROGRAMA OPENGL PARA A VISUALIZACAO DE CURVAS NO R4 --------" << endl << endl;
	cout << "INSTRUCOES" << endl;
	cout << "1) Pressionar tecla correspondente a funcionalidade desejada (ver abaixo)." << endl;
	cout << "2) Para o caso de funcionalidades com dois valores (ex: limite superior e inferior), pressionar <ESPACO> para alternar entre os valores." << endl;
	cout << "3) Pressionar as teclas \"+\" ou \"-\" para modificar o valor da funcionalidade selecionada." << endl << endl;
	cout << "TECLAS / FUNCIONALIDADES" << endl;
	cout << "1 - modificar o angulo theta1 (xy)" << endl;
	cout << "2 - modificar o angulo theta2 (yz)" << endl;
	cout << "3 - modificar o angulo theta3 (zw)" << endl;
	cout << "4 - modificar o angulo theta4 (xy)" << endl;
	cout << "5 - modificar o angulo theta5 (yz)" << endl;
	cout << "6 - modificar o angulo theta6 (xy)" << endl;
	cout << "F - modificar a funcao f(Z) plotada" << endl;
	cout << "R - modificar o dominio (limite inferior ou superior) da funcao f(Z) na coordenada r (radial)" << endl;
	cout << "T - modificar o dominio (limite inferior ou superior) da funcao f(Z) na coordenada t (angular)" << endl;
	cout << "N - modificar o numero de divisoes em cada coordenada para o desenho da curva" << endl;
	cout << "E - modificar o valor dos limites dos eixos cartesianos x, y, z, w exibidos no grafico" << endl << endl;
	cout << "COMANDOS EXTRAS" << endl;
	cout << "D - visualizar o dominio da funcao (projecao no plano xy)" << endl;
	cout << "I - visualizar a imagem da funcao (projecao no plano zw)" << endl;
}

// Fun��o main: monta console, janela e loop de visualiza��o (OPENGL)
int main(int argc, char** argv)
{
	console();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Visualizacao no R4");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	gluOrtho2D(-E, E, -E, E);
	glutMainLoop();
	return 0;
}