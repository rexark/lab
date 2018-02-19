#include <stdio.h>
#include <graphics.h>
#include <math.h>

void update(int *val, int mod)
{
	if(mod==0)
		return;
	if(mod>0)
		(*val)++;
	else
		(*val)--;
}

void main()
{
	int gd = DETECT, gm, i, xa, xb, ya, yb, Pk, dx, dy, x, y;

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	printf("\nEnter the value of Xa and Ya: ");
	scanf("%d%d", &xa, &ya);

	printf("\nEnter the value of Xb and Yb: ");
	scanf("%d%d", &xb, &yb);

	dx = xb-xa;
	dy = yb-ya;

	Pk = 2*abs(dy) - abs(dx);

	x = xa;
	y = ya;
	for(i=0; i<abs(dx); i++)
	{
		putpixel(x, y, WHITE);
		update(&x, dx);
		Pk += 2*abs(dy);
		if(abs(dx) == abs(dy))
			update(&y, dy);
		else if(Pk>0)
			Pk -= 2*abs(dx);
		else
			update(&y, dy);
		delay(1);
	}

	getch();
	closegraph();
}