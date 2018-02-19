#include <stdio.h>
#include <graphics.h>
#include <conio.h>

int inside = 0, left = 1, right = 2, bottom = 4, top = 8;
int xmin, ymin, xmax, ymax;

int outCode(double x, double y)
{
	int code = inside;
	
	if(x<xmin)
		code |= left;
	else if (x>xmax)
		code |= right;
	if (y<ymin)
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

void lineClip(double x0, double y0, double x1, double y1)
{
	int code0 = outCode(x0, y0), code1 = outCode(x1, y1), code;
	int accept = 0;
	double x, y;
	
	
	while(1)
	{
		delay(500);
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
	
	cleardevice();
	drawWindow();
	if(accept)
	{
		line(x0, y0, x1, y1);
	}
}

void main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	
	xmin = getmaxx()/3;
	xmax = 2*xmin;
	ymin = getmaxy()/3;
	ymax = 2*ymin;
	drawWindow();
	line(0, 0, 3*xmin, 3*ymin);
	delay(500);
	lineClip(0, 0, 3*xmin, 3*ymin);
	
	getch();
}
