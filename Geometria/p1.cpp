#include "Graphics.h"

int main(int argc, char **argv)
{
	Graphics graphics;
	int r,l;
	int gd = DETECT, gm = VGAMAX;
	int puntos[1000], count;

	printf("Apotema = ");
	scanf("%d", &r);

	printf("Lados = ");
	scanf("%d", &l);

	initgraph(&gd, &gm, NULL);

	int c = getmaxx()/2;
	int d = getmaxy()/2;

	int i = 0;
	int x1, y1, x2, y2, a1, a2;

	float ang,ang2;
	float delta = (2*PI/l);

	for (i = 1; i <= l; i++)
	{
		ang = i * delta;
		ang2 = (i+1) * delta ;

		x1 = (int)(r*cos(ang) + c);
		y1 = (int)(r*sin(ang) + d);
		x2 = (int)(r*cos(ang2) + c);
		y2 = (int)(r*sin(ang2) + d);

		count = graphics.DDALine(x1, y1, x2, y2, puntos);
	}

	graphics.generaArchivo(puntos, count);
	getch();
	closegraph();

	return 0;
}
