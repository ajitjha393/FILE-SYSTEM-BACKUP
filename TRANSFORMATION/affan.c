#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
Whole chart

Color	Value
BLACK	0
BLUE	1
GREEN	2
CYAN	3
RED	4
MAGENTA	5
BROWN	6
LIGHTGRAY	7
DARKGRAY	8
LIGHTBLUE	9
LIGHTGREEN	10
LIGHTCYAN	11
LIGHTRED	12
LIGHTMAGENTA	13
YELLOW	14
WHITE	15


*/
void scanFill();
void boundaryFill(int x, int y, int color1, int color2);
void main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    circle(250, 200, 20);
    boundaryFill(250, 200, 4, 15);
    getch();
    closegraph();
}

/*void scanFill()
{
	rectangle(300,220,340,260);
	boundaryFill(305,225,6,1);
}*/

void boundaryFill(int x, int y, int fillcolor, int boundarycolor)
{
    if (getpixel(x, y) != boundarycolor && getpixel(x, y) != fillcolor)
    {
        putpixel(x, y, fillcolor);
        delay(10);
        boundaryFill(x, y - 1, fillcolor, boundarycolor);
        boundaryFill(x, y + 1, fillcolor, boundarycolor);
        boundaryFill(x - 1, y, fillcolor, boundarycolor);
        boundaryFill(x + 1, y, fillcolor, boundarycolor);
    }
}