#include <stdio.h>
#include <graphics.h>

void drawCircle(int cx, int cy, int x, int y)
{
	int col = WHITE;
	putpixel(cx+x, cy+y, col);
	putpixel(cx+x, cy-y, col);
	putpixel(cx-x, cy+y, col);
	putpixel(cx-x, cy-y, col);
	putpixel(cx+y, cy+x, col);
	putpixel(cx+y, cy-x, col);
	putpixel(cx-y, cy+x, col);
	putpixel(cx-y, cy-x, col);
}

void main()
{
	int gd = DETECT, gm, cx, cy, r, d, x, y;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	printf("\nEnter the center and radius of the circle: ");
	scanf("%d%d%d", &cx, &cy, &r);

	d = 3 - 2*r;

	x = 0;
	y = r;
	while(x<y)
	{
		drawCircle(cx, cy, x, y);
		x++;
		d+=4*x;
		if(d<0)
			d+=6;
		else
		{
			d+=10-4*y;
			y--;
		}
		delay(100);
		//printf("%d\t", d);
	}

	getch();
}
