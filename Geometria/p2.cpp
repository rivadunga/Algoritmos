#include "Graphics.h"
#include <stdio.h>


int main()
{
	int gd=DETECT, gm;
	int radius;
  int grad;

	int puntos[10000];
	int count=0;

	printf("Radio = ");
	scanf("%d",&radius);
  printf("Grados = ");
  scanf("%d",&grad);

	initgraph(&gd, &gm, NULL);

	int c = getmaxx()/2;
	int d = getmaxy()/2;

	int xF = radius * cos(2*PI/grad);

	for (int x = 0; x < xF; x++){
			 putpixel(x+c,sqrt(pow(radius,2)-pow(x,2))+d,WHITE);

	}

	getch();
	closegraph();

	return 0;
}
