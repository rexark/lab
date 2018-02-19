#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define PI 3.14159265


int p[10], i, gd = DETECT, gm, ch, ox, oy;


void translate(float t1, float t2)
{
	
	for(i=0; i<4; i++)
	{
		p[2*i]+=t1;
		p[2*i+1]+=t2;
	}
	p[8]=p[0];
	p[9]=p[1];
}

void scale(float t1, float t2)
{
	
	for(i=0; i<4; i++)
	{
		p[2*i]*=t1;
		p[2*i+1]*=t2;
	}
		p[8]=p[0];
		p[9]=p[1];
}

void rotate(double angle)
{
	int t1, t2;
	angle *= PI/180;
	for(i=0; i<4; i++)
	{
		t1 = p[2*i];
		t2 = p[2*i+1];
		p[2*i] =  (t1*cos(angle) - t2*sin(angle));
		p[2*i+1] = (t1*sin(angle) + t2*cos(angle));
	}
	p[8]=p[0];
	p[9]=p[1];
}

void drawaxis()
{
	line(ox, 0, ox, 2*oy);
	line(0, oy, 2*ox, oy);	
}

void flipy()
{
	for(i=0; i<4; i++)
	{
		p[2*i+1] = - p[2*i+1];
	}
}

void flipx()
{
	for(i=0; i<4; i++)
	{
		p[2*i] = - p[2*i];
	}
}

void drawsomething()
{
	flipy();
	translate(ox, oy);
	drawaxis(ox, oy);
	drawpoly(5, p);
	translate(-ox,-oy);	
	flipy();
	for(i=0; i<4; i++)
		{
			printf("(%d, %d)\t", p[2*i], p[2*i+1]);
		}
}





void main()
{
	float t1, t2, tr1, tr2;
	int choice;
	double angle;
	
	

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	ox=getmaxx()/2;
	oy=getmaxy()/2;
	
	
	//printf("%d %d", ox, oy);

	for(i=0; i<4; i++)
	{
		printf("Enter coordinate %d: ", i+1);
		scanf("%d%d", &p[2*i], &p[2*i+1]);
		
	}
	
	p[8]=p[0];
	p[9]=p[1];

	
	clrscr();
	cleardevice();
	drawsomething();

	do
	{
		printf("\n1)Translation\t2)Scaling\t3)Rotation\t4)Reflection\nEnter the transformation: ");
		scanf ("%d", &ch);

		switch(ch)
		{
			case 1: printf("Enter the x and y translation: ");
					scanf("%f%f", &t1, &t2);
					translate(t1, t2);
					break;

			case 2: printf("Enter the x and y scale: ");
					scanf("%f%f", &t1, &t2);
					printf("\nEnter the reference point: ");
					scanf("%f%f", &tr1, &tr2);
					translate(-tr1, -tr2);
					scale(t1, t2);
					translate(tr1, tr2);
					break;
			case 3: printf("Enter the angle: ");
					scanf("%lf", &angle);
					printf("\nEnter the reference point:");
					scanf("%f%f", &tr1, &tr2);
					translate(-tr1, -tr2);
					rotate(angle);
					translate(tr1, tr2);
				break;
			case 4:	printf("1. X-axis\t2. Y-axis\t3. XY line\t4. Origin\nEnter your choice: ");
					scanf("%d", &choice);
					if(choice==3)
					{
						for(i=0; i<4; i++)
						{
							t1 = p[2*i];
							p[2*i] = p[2*i+1];
							p[2*i+1]=t1;
						}
					}
					else if(choice==1)
					{
						flipx();
					}
					else if (choice==2)
					{
						flipy();
					}
					else if (choice==4)
					{
						flipx();
						flipy();
					}
					else
						break;
					p[8]=p[0];
					p[9]=p[1];
					break;


		}
		clrscr();
		cleardevice();
		drawsomething();
			
		
	}while(ch<=4 && ch>=1);
	
	getch();
}
