#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void main()
{
    int gd = DETECT, gm, x = 320, y = 240;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setcolor(GREEN);
    line(x - 20, y - 20, x + 20, y - 20);
    setcolor(BLUE);
    line(x + 20, y - 20, x + 20, y + 20);
    setcolor(YELLOW);
    line(x + 20, y + 20, x - 20, y + 20);
    setcolor(MAGENTA);
    line(x - 20, y + 20, x - 20, y - 20);

    getch();
    closegraph();
}