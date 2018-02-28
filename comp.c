#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define PI 3.14159


float p[20][3];
int n, ox, oy;

float identity[3][3];
				
void clearid()
{
	int i,j;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			identity[i][j] = i==j?1:0;
}

void matmul()
{
	float c[3];
	int i, j, k;
	for(i=0; i<n; i++)
	{
		for(j=0; j<3; j++)
		{
			c[j] = 0;
			for(k=0; k<3; k++)
				c[j] += identity[j][k] * p[i][k];
		}
		p[i][0] = c[0];
		p[i][1] = c[1];
	}
}

void setidentity(char mode, double param1, double param2)
{
	int i, j;
	clearid();
	switch(mode)
	{
		case 't':	identity[0][2] = param1;
					identity[1][2] = param2;
					break;
					
		case 's':	identity[0][0] = param1;
					identity[1][1] = param2;
					break;
					
		case 'r':	param1 *= PI/180;
					identity[0][0] = cos(param1);
					identity[0][1] = -sin(param1);
					identity[1][0] = sin(param1);
					identity[1][1] = cos(param1);
					break;
	}
	matmul();
	/*for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
			printf("%f\t", identity[i][j]);
		printf("\n");
	}*/
		
		
}

void drawlines()
{
	int i;
	setidentity('t', ox, oy);
	for(i=0; i<n-1; i++)
		line(p[i][0], p[i][1], p[i+1][0], p[i+1][1]);
	line(p[i][0], p[i][1], p[0][0], p[0][1]);
	setidentity('t', -ox, -oy);
}

void drawaxis()
{
	line(0, oy, 2*ox, oy);
	line(ox, 0, ox, 2*oy);
}



void main()
{
	int gd = DETECT, gm, i, ch;
	char mode;
	float p1, p2;
	
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	
	ox = getmaxx()/2;
	oy = getmaxy()/2;
	printf("\nEnter the number of vertices: ");
	scanf("%d", &n);
	for(i=0; i<n; i++)
	{
		printf("Enter vertex %d: ", i+1);
		scanf("%f %f", &p[i][0], &p[i][1]);
		p[i][2] = 1;
		putpixel(p[i][0], p[i][1], WHITE);
	}
	clrscr();
	cleardevice();
	drawaxis();
	drawlines();
	
	/*for(i=0; i<n; i++)
	{
		printf("\n(%f, %f) ", p[i][0], p[i][1]);
	}*/
	
	do
	{
		printf("\n1) Translate\t2) Scale 3) Rotate\nEnter the transformation to be performed: ");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1:	printf("\nEnter translation factor: ");
					scanf("%f %f", &p1, &p2);
					mode = 't';
					break;
			case 2: printf("\nEnter the scaling factor: ");
					scanf("%f %f", &p1, &p2);
					mode = 's';
					break;
			case 3: printf("\nEnter the angle: ");				
					scanf("%f", &p1);
					p2 = 0;
					mode = 'r';
		}
		
		clrscr();
		cleardevice();
		setidentity(mode, p1, p2);
		drawaxis();
		drawlines();
	}while(ch>=1 && ch<=3);
	
	
	/*for(i=0; i<n; i++)
	{
		printf("\n(%f, %f) ", p[i][0], p[i][1]);
	}*/
	
	getch();
}
