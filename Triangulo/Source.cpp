/*
"Disofenix 117"
Diego Esteban Suarez C.
Universidad Militar Nueva Granada
2018
*/
//#include "readerPNMImageFile.h"
#include <stdlib.h>
#include <math.h>
#include<stdio.h>

#ifdef GL
#include <GL\glut.h>
#else
#include "glut.h"
#endif // GL

//variables globales
int Xmi, Ymi;		// Punto inicial de click
int H, W;			//variables de ventana
int Xme, Yme;       // Punto final de click
int Xcu, Ycu;		// Coordenadas del cursor
int clic;//variable para el clic
float const pi = 2 * 3.11416;
float matriz[2][1];
typedef struct
{
	float x;
	float y;
} punto;
punto p1, p2, p3, memoria, p4, aux;


enum State
{
	Dibujar,
	Inspeccionar,
	Choose,
};
State modo;



//////////////////////////////////////////////////////////////////////////
//Definicion de Funciones
//////////////////////////////////////////////////////////////////////////
void Inicio(void);
void DrawCursor(int Xc, int Yc);
void dibujarLineaBresenham(punto pt1, punto pt2);
void ConfigureWindow(int newW, int newH);
void OnResizeWindow(int width, int height);
void onRender(void);
//////////////////////////////////////////////////////////////////////////
//FUNCIONES BASICAS PARA OPENGL
//////////////////////////////////////////////////////////////////////////

void Inicio(void)//iniciacion de variables
{
	H = 1000, W = 1000;
	Xmi = 0;
	Xme = 0;
	Ymi = 0;
	Yme = 0;
	Xcu = 0;
	Ycu = 0;
	clic = 0;
	modo = Dibujar;


}
void OnMouse(int btn, int state, int x, int y) //funcion que captura clics
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			Xcu = x;
			Ycu = y;
			if (modo == Dibujar)
			{

				switch (clic)
				{
				case 0:
				{
					p1.x = x;
					p1.y = y;
					clic = 1;
					//matriz[0][0] = p1.x;
					//matriz[0][1] = p1.y;
					break;
				}

				case 1:
				{
					
					p2.x = x;
					p2.y = y;
					//matriz[1][0] = p2.x;
					//matriz[1][1] = p2.y;
					clic = 2;
					break;
				}
				case 2:
				{
					
					p3.x = x;
					p3.y = y;
					//matriz[2][0] = p3.x;
					//matriz[2][1] = p3.y;
					clic = 0;
					glutPostRedisplay();
					glFlush();
					break;
				}
				}
			}
			else if (modo == Inspeccionar)
			{
				p4.x = x;
				p4.y = y;
				glutPostRedisplay();
				glFlush();
			}

		}
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCursor(Xcu, Ycu);
}
void OnMouseMove(int X, int Y)
{
	Xcu = X;
	Ycu = Y;
	Xme = Xcu;
	Yme = Ycu;

	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCursor(Xcu, Ycu);

	glutPostRedisplay();
}
void OnKeyboard(unsigned char key, int x, int y)// Se configura el modo de graficación en el teclado
{
	switch (key)
	{
	case 'x':
	case 'X':
	{
		exit(0);
		break;
	}
	case 'i':
	case'I':
	{
		modo = Inspeccionar;
		break;
	}
	case 'd':
	case'D':
	{
		modo = Dibujar;
	}
	}


}


//////////////////////////////////////////////////////////////////////////
//FUNCIONES
//////////////////////////////////////////////////////////////////////////
void DrawCursor(int Xc, int Yc)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2i(Xc - 5, Yc - 5);
	glVertex2i(Xc - 5, Yc + 5);
	glVertex2i(Xc + 5, Yc + 5);
	glVertex2i(Xc + 5, Yc - 5);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2i(Xc - 1, Yc - 1);
	glVertex2i(Xc - 1, Yc + 1);
	glVertex2i(Xc + 1, Yc + 1);
	glVertex2i(Xc + 1, Yc - 1);
	glEnd();

}
void dibujar(int xo, int yo, int x1)
{
	glBegin(GL_POINTS);
	for (int i = xo; i <= x1; i++) {
		glVertex2i(i, yo);
	}
	glEnd();
}
void DrawVerticalLine(int Yi, int Ye, int X)
{
	int y;
	for (y = Yi; y <= Ye; y++)
	{
		glVertex2i(X, y);
	}
}
void DrawHorizontalLine(int Xi, int Xe, int Y)
{
	int x;
	for (x = Xi; x <= Xe; x++)
	{
		glVertex2i(x, Y);
	}
}
void FillRectangle(int Xi, int Yi, int Rw, int Rh)
{
	int y;
	int ye = Yi + Rh;
	int xe = Xi + Rw;

	glBegin(GL_POINTS);
	for (y = Yi; y <= ye; y++)
	{
		DrawHorizontalLine(Xi, xe, y);
	}
	glEnd();
}
void DrawRectangle(int Xi, int Yi, int Rw, int Rh)
{
	int ye = Yi + Rh;
	int xe = Xi + Rw;

	glBegin(GL_POINTS);
	DrawHorizontalLine(Xi, xe, Yi);
	DrawHorizontalLine(Xi, xe, ye);
	DrawVerticalLine(Yi, ye, Xi);
	DrawVerticalLine(Yi, ye, xe);
	glEnd();
}
void puntomendio()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glColor4f(0.10f, 0.69f, 0.40f, 0.0f);
	for (int i = 0; i < 50000; i++)
	{
		int random;
		random = rand() % 3;
		if (random == 0)
		{
			p4.x = (p4.x + p1.x) / 2;
			p4.y = (p4.y + p1.y) / 2;
			glVertex2i(p4.x, p4.y);
		}
		else if (random == 1)
		{
			p4.x = (p4.x + p2.x) / 2;
			p4.y = (p4.y + p2.y) / 2;
			glVertex2i(p4.x, p4.y);
		}
		else if (random == 2)
		{
			p4.x = (p4.x + p3.x) / 2;
			p4.y = (p4.y + p3.y) / 2;
			glVertex2i(p4.x, p4.y);
		}
	}
	glEnd();
}

void ordenamiento()
{

	if (p1.y <= p2.y && p1.y <= p3.y)
	{
		if (p2.y <= p3.y)
		{
		}
		else
		{
			memoria.x = p2.x;
			memoria.y = p2.y;
			p2.x = p3.x;
			p2.y = p3.y;
			p3.x = memoria.x;
			p3.y = memoria.y;
		}
	}
	if (p2.y <= p1.y && p2.y <= p3.y)
	{
		memoria.x = p1.x;
		memoria.y = p1.y;
		p1.x = p2.x;
		p1.y = p2.y;
		p2.x = memoria.x;
		p2.y = memoria.y;

		if (p2.y <= p3.y)
		{
		}
		else
		{
			memoria.x = p2.x;
			memoria.y = p2.y;
			p2.x = p3.x;
			p2.y = p3.y;
			p3.x = memoria.x;
			p3.y = memoria.y;
		}
	}
	if (p3.y <= p1.y && p3.y <= p2.y)
	{
		memoria.x = p1.x;
		memoria.y = p1.y;
		p1.x = p3.x;
		p1.y = p3.y;
		p3.x = memoria.x;
		p3.y = memoria.y;

		if (p2.y <= p3.y)
		{
		}
		else
		{
			memoria.x = p2.x;
			memoria.y = p2.y;
			p2.x = p3.x;
			p2.y = p3.y;
			p3.x = memoria.x;
			p3.y = memoria.y;
		}
	}
}

void dibujarLineaBresenham(punto A, punto B)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(0.10f, 0.69f, 0.40f, 0.0f);
	glBegin(GL_POINTS);
	/*Recta forma cartesiana y=mx+b
	m=dy/dx
	Recta forma general f(x,y)=Ax+By+C=0
	donde m= -A/B   y  b= -C/B*/
	int dx, dy, dE, dNE, De, Dne, d, D, x, y, f, mv;
	dx = labs(B.x - A.x);
	dy = labs(B.y - A.y);
	//Si (dx > dy) entonces se toma que el negativo será B en lugar de A por ende A= dy, B= -dx y C= -bdx
	//Si (dx < dy) entonces se toma que el negativo será A en lugar de B por ende A= -dy, B= dx y C= bdx
	d = 2 * dy - dx; // Es el dk cuando (dx > dy) = (dy -1/2 dx) se multiplicó x2 para quitar los racionales.
	D = 2 * dx - dy; // Es el dk cuando (dx < dy) = (dx -1/2 dy) se multiplicó x2 para queitar los racionales
	dE = 2 * dy; // dE= dk+1 cuando d<0 y cuando (dx > dy)
	De = 2 * dx; // De= dk+1 cuando d<0 y cuando (dx < dy)
	dNE = 2 * (dy - dx); // dNe = dk+1 cuando d>=0 y cuando (dx > dy)
	Dne = 2 * (dx - dy); //Dne = dk+1 cuando d>=0 y cuando (dx < dy)
	x = A.x;
	y = A.y;
	mv = 1; // Dependiendo del octante en que se encuentre indica si la variable que lleva el punto medio aumenta o disminuye.
	if (dx > dy) // Se ubica desde (pi/4 , 7pi/4) u (3pi/4 , 5pi/4 )
	{
		if (A.x > B.x)
		{
			x = B.x;
			y = B.y;
			f = A.x; // El punto f siempre se ubicará hacia la derecha por organización y cumplimiento de la condición
					 //while dentro de un determinado octante
			if (B.y > A.y)
				mv = -1;
		}
		else
		{
			x = A.x;
			y = A.y;
			f = B.x;
			if (A.y > B.y)
				mv = -1;
		}
		glVertex2i(x, y);
		while (x < f)
		{
			x++;
			if (d < 0)
				d = d + dE;
			else
			{
				y = y + mv;
				d = d + dNE;
			}
			glVertex2i(x, y);
		}
	}   // Desde aquí se refleja en los octantes faltantes desde (pi/4 , 3pi/4) u (5pi/4 , 7pi/4)
	else
	{
		if (A.y > B.y)
		{
			x = B.x;
			y = B.y;
			f = A.y;
			if (B.x > A.x)
				mv = -1;
		}
		else
		{
			x = A.x;
			y = A.y;
			f = B.y;
			if (A.x > B.x)
				mv = -1;
		}
		glVertex2i(x, y);
		while (y < f)
		{
			y++;
			if (D < 0)
			{
				D = D + De;
			}
			else
			{
				x = x + mv;
				D = D + Dne;
			}
			glVertex2i(x, y);
		}
	}
	glEnd();
}
void RellenoTriangulo(punto pt1, punto pt2, punto pt3) {
	ordenamiento();
	int x = pt1.x;
	int y = pt1.y;
	float xo;
	float x1;
	xo = x1 = x;

	float dx1 = (pt2.x - pt1.x);
	float dy1 = (pt2.y - pt1.y);
	float dx2 = (pt3.x - pt2.x);
	float dy2 = (pt3.y - pt2.y);
	float dx3 = (pt3.x - pt1.x);
	float dy3 = (pt3.y - pt1.y);

	while (y <= pt2.y)
	{
		xo += dx1 / dy1;
		x1 += dx3 / dy3;

		if (xo > x1) {
			dibujar(x1, y, xo);
		}
		else
		{
			dibujar(xo, y, x1);
		}

		y++;

	}

	while (y <= pt3.y)
	{
		xo += dx2 / dy2;
		x1 += dx3 / dy3;
		if (xo > x1) {
			dibujar(x1, y, xo);
		}
		else
		{
			dibujar(xo, y, x1);
		}

		y++;

	}

}
void dibujarTriangulo()
{
	dibujarLineaBresenham(p1, p2);
	dibujarLineaBresenham(p2, p3);
	dibujarLineaBresenham(p3, p1);
	//RellenoTriangulo(p1, p2, p3);
}

bool testInOut(punto A, punto v)
{

	float theta = 0, magnitud, ProdPunt;
	float e = exp(1);
	punto Cp, Bp, B, C, temp;
	magnitud = sqrtf(pow(v.x - A.x, 2) + pow(v.y - A.y, 2));
	Cp.x = (A.x - v.x) / magnitud;
	Cp.y = (A.y - v.y) / magnitud;
	C = Cp;
	for (int i = 1; i <= 3; i++)
	{
		B.x = A.x - v.x;
		B.y = A.y - v.y;
		magnitud = sqrtf(pow(B.x - C.x, 2) + pow(B.y - C.y, 2));
		B.x = (B.x / magnitud);
		B.y = (B.y / magnitud);
		ProdPunt = C.x*B.x + C.y*B.y;
		theta += acos(ProdPunt);
		C = B;
	}

	ProdPunt = C.x*Cp.x + C.y*Cp.y;
	theta += acosf(ProdPunt);
	return (fabs(theta - 2 * pi) < e);
}

//////////////////////////////////////////////////////////////////////////
//FUNCIONES BASICAS PARA OPENGL
//////////////////////////////////////////////////////////////////////////
void ConfigureWindow(int newW, int newH)//Funcion de configuracion de la ventana de graficacion el puerto de vista

{
	glViewport(0, 0, newW, newH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, newW, newH, 0);
}
void OnResizeWindow(int width, int height)//Funcion cuando la ventana de la GUI cambia de tamaño
{
	ConfigureWindow(width, height);

	W = width;
	H = height;
}
void onRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ConfigureWindow(W, H);
	if (modo == Dibujar)
	{
		dibujarTriangulo();
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawRectangle(10, 10, 100, 100);

	}
	else if (modo == Inspeccionar)
	{
		puntomendio();

		glColor4f(0.10f, 0.69f, 0.40f, 0.0f);
		glBegin(GL_LINES);
		glVertex2i(10, 10);
		glVertex2i(100, 100);
		glVertex2i(10, 60);
		glVertex2i(100, 100);
		glEnd();

		glColor4f(0.10f, 0.69f, 0.40f, 0.0f);
		FillRectangle(10, 10, 100, 100);
	}
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCursor(Xcu, Ycu);


	glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////
//FUNCION PRINCIPAL
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Inicio();
	glutCreateWindow("Disofenix 117 - 3er Corte");
	glutReshapeWindow(W, H);
	glutDisplayFunc(onRender);
	glutReshapeFunc(OnResizeWindow);
	glutMouseFunc(OnMouse);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(OnKeyboard);
	glutMainLoop();


	return 0;
}