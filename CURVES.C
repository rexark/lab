#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>

int p[20], knots[20];

int factorial(int n)
{
	return n<2?1:n*factorial(n-1);
}

int nCr(int n, int r)
{
	return factorial(n)/(factorial(n-r)*factorial(r));
}

void bezier(int cp)
{
	int i;
	double u, bx, by;

	for(u=0; u<1.000; u+=0.005)
	{
		bx=by=0;
		for(i=0; i<cp; i++)
		{
			bx+=nCr(cp-1, i)*pow(u, i)*pow(1-u, cp-1-i)*p[2*i];
			by+=nCr(cp-1, i)*pow(u, i)*pow(1-u, cp-1-i)*p[2*i+1];
		}
		putpixel(bx, by, RED);
		delay(10);
	}
}

double N(int i, int k, double t)
{
	if(k==1)
	{
		if(t>=knots[i] && t<knots[i+1])
			return 1;
		else
			return 0;
	}
	else
		return ((t-knots[i])/(knots[i+k-1] - knots[i]))*N(i, k-1, t)
			+  ((knots[i+k]-t)/(knots[i+k]-knots[i+1]))*N(i+1, k-1, t);
}

void bspline(int cp)
{
	int n = cp-1, k = 3, i;
	double t, x, y;

	for(i=0; i<n+k+2; i++)
	{
		knots[i] = i+1;
	}

	for(t=3; t<=5; t+=0.01)
	{
		x=y=0;
		for(i=0; i<=n; i++)
		{
			x += N(i, k, t)*p[2*i];
			y += N(i, k, t)*p[2*i+1];
		}
		putpixel(x, y, CYAN);
		delay(10);
	}

}


void main()
{
	int gd = DETECT, gm, cp, i;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	printf("\nEnter the number of control points: ");
	scanf("%d", &cp);

	for(i=0; i<cp; i++)
	{
		printf("\nEnter control point %d", i+1);
		scanf("%d%d", &p[2*i], &p[2*i+1]);
		putpixel(p[2*i], p[2*i+1], WHITE);
	}
	drawpoly(cp, p);
	setcolor(RED);
	bspline(cp);
	bezier(cp);
	
	getch();
}
