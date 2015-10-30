#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <algorithm>
#define PI 3.14159265

class Graphics
{
	public:

		int DDALine(int x0, int y0, int x1, int y1, int puntos[])
		{

			if (x0 >= x1 && y0 >= y1){
				std::swap(x0,x1);
				std::swap(y0,y1);
			}

			int maxY, i;

			float dx, dy, m, x, y;

			i=0;

			dx=x1-x0;
			dy=y1-y0;

			maxY=getmaxy();

			if (dx == 0) /* Es una línea vertical */
			{
				for(y = y0; y <= y1; ++y)
				{
					putpixel(x0, maxY-y, WHITE);
					puntos[i] = x0;
					puntos[i+1] = y;
					i += 2;
				}
			}
			else if (dy == 0) /* Es una línea horizontal */
			{
				for(x = x0; x <= x1; ++x)
				{
					putpixel(x, maxY-y0, WHITE);
					puntos[i] = x0;
					puntos[i+1] = y;
					i += 2;
				}
			}
			else if (dy <= dx) /* Es una línea con pendiente < 1 */
			{
				m = dy/dx;
				y = y0;

				for(x = x0; x <= x1; ++x)
				{
					putpixel(x, (int)(maxY-y), WHITE);
					puntos[i] = x;
					puntos[i+1] = (int)y;
					i += 2;
					y = y + m;
				}
			}
			else /* Es una línea con pendiente > 1 */
			{
				m = dx/dy;
				x = x0;
				for(y = y0; y <= y1; ++y)
				{
					putpixel((int)x, maxY-y, WHITE);
					puntos[i] = (int)x;
					puntos[i+1] = y;
					i += 2;
					x = x + m;
				}
			}

			return i;
		 }




		 /* Dibuja los puntos por simetría en los demás cuadrantes */
		 int ellipsePoints(int x, int y, int puntos[], int i)
		 {
			 int maxx = getmaxx()/2;
			 int maxy = getmaxy()/2;

			 putpixel(maxx+x,maxy+y,WHITE);

			 puntos[i]=maxx+x;
			 puntos[i+1]=maxy+y;
			 i+=2;

			 putpixel(maxx-x,maxy+y,WHITE);
			 putpixel(maxx+x,maxy-y,WHITE);
			 putpixel(maxx-x,maxy-y,WHITE);

			 return i;
		 }

		 /* Algoritmo MidPointElipse */
		 int midPointEllipse(int a,int b, int puntos[])
		 {
			 int i = 0;
			 double d2;
			 int x=0;
			 int y=b;

			 double dl=b*b-(a*a*b)+(0.25*a*a);

			 putpixel(x,y, WHITE);

			 while((a*a*(y-0.5))>(b*b*(x+1)))
			 {
				 if(dl<0)
					 dl+=b*b*(2*x+3);
				 else
				 {
					 dl+=b*b*(2*x+3)+a*a*(-2*y+2);
					 y--;
				 }
				 x++;

				 i = ellipsePoints(x, y, puntos, i);
			 }

			 d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;

			 while(y>0)
			 {
				 if(d2<0)
				 {
					 d2+=b*b*(2*x+2)+a*a*(-2*y+3);
					 x++;
				 }
				 else
					 d2+=a*a*(-2*y+3);
				 y--;

				 i = ellipsePoints(x, y, puntos, i);
			 }

			 return i;
		 }


		void generaArchivo(int puntos[], int count)
		{
			FILE *fp;
			int i,np;
			fp=fopen("puntos.txt","w");
			fprintf(fp,"%s","Los puntos dibujados son:\n");
			np=0;

			for(i = 0; i < count; i += 2){
				fprintf(fp,"(%d, %d) ", puntos[i], puntos[i+1]);
				np++;
				if(np==5) { fprintf(fp,"\n"); np=0; }
			}

			fclose(fp);
		}

};
