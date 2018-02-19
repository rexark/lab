#include <stdio.h>
#include <graphics.h>
#include <conio.h>

int p[20], xmin, xmax, ymin, ymax, n;
int left = 1, right = 2, bottom = 4, top = 8, inside = 0;

struct line
{
	int x1, y1, x2, y2;
} lines[10];

int outCode(int x, int y)
{
	int code = inside;
	if(x<xmin)
		code |= left;
	else if(x>xmax)
		code |= right;
	if(y<ymin)
		code |= bottom;
	else if(y>ymax)
		code |= top;
	return code;
}

void drawWindow()
{
	line(xmin, 0, xmin, getmaxy());
	line(xmax, 0, xmax, getmaxy());
	line(0, ymin, getmaxx(), ymin);
	line(0, ymax, getmaxx(), ymax);
}

void clip(int i)
{
	int x0 = lines[i].x1, y0 = lines[i].y1, x1 = lines[i].x2, y1 = lines[i].y2;
	int code0 = outCode(x0, y0), code1 = outCode(x1, y1), code;
	int accept = 0;
	double x, y;
	
	//printf("\n(%d, %d) and (%d, %d)", x0, y0, x1, y1);
	while(1)
	{
		if(!(code0 | code1))
		{
			accept = 1;
			break;
		}
		else if (code0 & code1)
			break;
			
		else
		{
			code = code0?code0:code1;
			
			if(code & top)
			{
				x = x0 + (x1-x0)*(ymax-y0)/(y1-y0);
				y = ymax;
			}
			else if (code & bottom)
			{
				x = x0 + (x1-x0)*(ymin-y0)/(y1-y0);
				y = ymin;
			}
			else if (code & right)
			{
				y = y0 + (y1-y0)*(xmax-x0)/(x1-x0);
				x = xmax;
			}
			else if(code & left)
			{
				y = y0 + (y1-y0)*(xmin-x0)/(x1-x0);
				x = xmin;
			}
			
			if(code == code0)
			{
				x0 = x;
				y0 = y;
				code0 = outCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				code1 = outCode(x1, y1);
			}
		}
	}
	
	if(accept)
	{
		lines[i].x1 = x0;
		lines[i].y1 = y0;
		lines[i].x2 = x1;
		lines[i].y2 = y1;
	}
	else
	{
		lines[i].x1 = 0;
		lines[i].y1 = 0;
		lines[i].x2 = 0;
		lines[i].y2 = 0;
	}
	
	//printf("\n   to(%d, %d) and (%d, %d)", x0, y0, x1, y1);
}

void drawLines()
{
	int i;
	for(i=0; i<n; i++)
	{
		
		line(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
		//printf("\n(%d, %d) and (%d, %d)", lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
	}
		
}

void main()
{
	int gd = DETECT, gm, i;
	
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	
	printf("\nEnter the number of vertices: ");
	scanf("%d", &n);
	
	for(i=0; i<n; i++)
	{
		printf("\nEnter vertex %d: ", i+1);
		scanf("%d%d", &p[2*i], &p[2*i+1]);
		putpixel(p[2*i], p[2*i+1], WHITE);
	}
	p[2*i] =  p[0];
	p[2*i+1] = p[1];
	
	for(i=0; i<n; i++)
	{
		lines[i].x1 = p[2*i];
		lines[i].y1 = p[2*i+1];
		lines[i].x2 = p[2*(i+1)];
		lines[i].y2 = p[2*(i+1)+1];
	}
	
	
	
	xmin = getmaxx()/3;
	ymin = getmaxy()/3;
	xmax = 2*xmin;
	ymax = 2*ymin;
	drawWindow();
	drawLines();
	
	
	delay(500);
	for(i=0; i<n; i++)
	{
		//printf("Clipping line %d", i+1);
		clip(i);
		/*delay(100);
		clrscr();
		cleardevice();
		drawWindow();
		drawLines();*/
	}
	cleardevice();
	drawWindow();
	drawLines();
	/*
	//drawpoly(n+1, p);
	delay(500);
	clip(0, left);
	delay(500);
	clip(1, right);
	delay(500);
	//clip(2, bottom);
	*/
	
	getch();
}
