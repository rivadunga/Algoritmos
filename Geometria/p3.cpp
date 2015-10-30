#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include "Graphics.h"
#define PI 3.14159265

void imprimirPrisma(int, int, int, int);
void imprimirCono(int, int, int);

int main(int argc, char **argv)
{
	int SX,SY,SZ,L;
	int gd = DETECT, gm = VGAMAX;

	printf("Largo: ");
	scanf("%d", &SY);

	printf("Ancho: ");
	scanf("%d", &SX);

	printf("Altura: ");
	scanf("%d", &SZ);

	printf("Lados (0 para cono): ");
	scanf("%d", &L);

	initgraph(&gd, &gm, NULL);
	if (L == 3 	|| L == 4)
		imprimirPrisma(L,SX,SY,SZ);

	if (L == 0)
		imprimirCono(SX,SY,SZ);

	return 0;
}


void imprimirPrisma(int lados, int SX, int SY, int SZ)
{
		Graphics graphics;
	  int puntos[1000], count;

		int c = getmaxx()/4;
		int d = getmaxy()/4;

		float p1B[] = {c,d};
		float p2B[] = {c+SX,d};
		float p3B[] = {p1B[0]+SY*cos(2*PI/45),p1B[1]+SY*sin(2*PI/45)};
		float p4B[] = {p2B[0]+SY*cos(2*PI/45),p2B[1]+SY*sin(2*PI/45)};

		float p1T[] = {p1B[0],p1B[1]+SZ};
		float p2T[] = {p2B[0],p2B[1]+SZ};
		float p3T[] = {p3B[0],p3B[1]+SZ};
		float p4T[] = {p4B[0],p4B[1]+SZ};


		count = graphics.DDALine(p1B[0],p1B[1],p2B[0],p2B[1], puntos);
		count = graphics.DDALine(p1B[0],p1B[1],p3B[0],p3B[1], puntos);
		if (lados == 4){
			count = graphics.DDALine(p2B[0],p2B[1],p4B[0],p4B[1], puntos);
			count = graphics.DDALine(p3B[0],p3B[1],p4B[0],p4B[1], puntos);
			count = graphics.DDALine(p2T[0],p2T[1],p4T[0],p4T[1], puntos);
			count = graphics.DDALine(p3T[0],p3T[1],p4T[0],p4T[1], puntos);
		}else{
			count = graphics.DDALine(p2B[0],p2B[1],p3B[0],p3B[1], puntos);
			count = graphics.DDALine(p2T[0],p2T[1],p3T[0],p3T[1], puntos);
		}

		count = graphics.DDALine(p1T[0],p1T[1],p2T[0],p2T[1], puntos);
		count = graphics.DDALine(p1T[0],p1T[1],p3T[0],p3T[1], puntos);

		count = graphics.DDALine(p1B[0],p1B[1],p1T[0],p1T[1], puntos);
		count = graphics.DDALine(p2B[0],p2B[1],p2T[0],p2T[1], puntos);
		count = graphics.DDALine(p3B[0],p3B[1],p3T[0],p3T[1], puntos);

		if (lados == 4)
			count = graphics.DDALine(p4B[0],p4B[1],p4T[0],p4T[1], puntos);

		graphics.generaArchivo(puntos, count);
		getch();
		closegraph();
}

void imprimirCono(int SX, int SY, int SZ)
{
	Graphics graphics;
	int puntos[20000];
	int count=0;
	int a = SX; int b = SY*sin(2*PI/45.0);

	int c = getmaxx()/2;
	int d = getmaxy()/2;
	int p1[] = {c-SX, d};
	int p2[] = {c,d+SZ};
	int p3[] = {c+SX,d};
	int p4[] = {c,d-b};

	count = graphics.midPointEllipse(a, b, puntos);

	count = graphics.DDALine(p1[0],p1[1],p2[0],p2[1], puntos);
	count = graphics.DDALine(p2[0],p2[1],p3[0],p3[1], puntos);
	count = graphics.DDALine(p4[0],p4[1],p2[0],p2[1], puntos);

	graphics.generaArchivo(puntos, count);

	getch();
	closegraph();

}
