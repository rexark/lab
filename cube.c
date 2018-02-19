#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>

#define PI 3.14159

float x[8], y[8], z[8];

void rotate(double angle, char axis)
{
	float t1, t2;
	int i;
	angle *= PI/180;
	switch(axis)
	{
		case 'z':	for(i=0; i<8; i++)
					{
						t1 = x[i];
						t2 = y[i];
						x[i] = t1*cos(angle) - t2*sin(angle);
						y[i] = t1*sin(angle) + t2*cos(angle);
					}
					break;
		case 'y':	for(i=0; i<8; i++)
					{
						t1 = x[i];
						t2 = z[i];
						x[i] = t1*cos(angle) + t2*sin(angle);
						z[i] = -t1*sin(angle) + t2*cos(angle);
					}
					break;
		case 'x':	for(i=0; i<8; i++)
					{
						t1 = y[i];
						t2 = z[i];
						y[i] = t1*cos(angle) - t2*sin(angle);
						z[i] = t1*sin(angle) + t2*cos(angle);
					}
					break;
	}
}

void translate(float tx, float ty)
{
	int i;
	for(i=0; i<8; i++)
	{
		x[i]+=tx;
		y[i]+=ty;
	}
}

void drawCube()
{
	translate(getmaxx()/2, getmaxy()/2);
	line(x[0], y[0], x[1], y[1]); 
	line(x[0], y[0], x[2], y[2]);
	line(x[0], y[0], x[4], y[4]);
	
	line(x[7], y[7], x[6], y[6]);
	line(x[7], y[7], x[5], y[5]);
	line(x[7], y[7], x[3], y[3]);
	
	line(x[3], y[3], x[2], y[2]);
	line(x[3], y[3], x[1], y[1]);
	
	line(x[5], y[5], x[1], y[1]);
	line(x[5], y[5], x[4], y[4]);
	
	line(x[4], y[4], x[6], y[6]);
	line(x[6], y[6], x[2], y[2]);
	translate(-getmaxx()/2, -getmaxy()/2);
}

void main()
{
	int gd = DETECT, gm, i, ch;
	float a, t1, t2;
	char axis;
	
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	
	printf("Enter the length of the cube: ");
	scanf("%f", &a);
	
	for(i=0; i<8; i++)
	{
		z[i] = i%2*a;
		y[i] = (i/2)%2*a;
		x[i] = (i/4)%2*a;
		//printf("\n %f, %f, %f", x[i], y[i], z[i]);
	}
	
	/*cleardevice();
	rotate(70, 'x');
	rotate(30, 'y');
	drawCube();*/
	
	
	/*while(!kbhit())
	{
		cleardevice();
		rotate(1, 'x');
		rotate(1, 'y');
		rotate(1, 'z');
		drawCube();
		delay(30);
	}*/
	
	do
	{
		printf("\n1)Translation\t2)Rotation\nEnter the transformation: ");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1: printf("Enter tx and ty: ");
					scanf("%f%f", &t1, &t2);
					translate(t1, t2);
					break;
			case 2:	printf("Enter the angle and axis: ");
					scanf("%f %c", &t1, &axis);
					rotate(t1, axis);
					break;
		}
		clrscr();
		cleardevice();
		
		drawCube();
	}while(ch!=0);
	
	
	getch();
}
