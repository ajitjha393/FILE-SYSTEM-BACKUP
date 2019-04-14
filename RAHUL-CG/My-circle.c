#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void Circle(int r, int xc, int yc)
{
    int P, x = 0, y = r, i, Xmax, Ymax;
    Xmax = getmaxx();
    Ymax = getmaxy();
    P = 1 - r;
    while (x <= y)
    {
        putpixel(x + (Xmax / 2) + xc, (Ymax / 2) - y + yc, WHITE);
        putpixel(-x + (Xmax / 2) + xc, (Ymax / 2) - y + yc, WHITE);
        putpixel(x + (Xmax / 2) + xc, (Ymax / 2) + y + yc, WHITE);
        putpixel(-x + (Xmax / 2) + xc, (Ymax / 2) + y + yc, WHITE);
        putpixel(y + (Xmax / 2) + xc, (Ymax / 2) - x + yc, WHITE);
        putpixel(-y + (Xmax / 2) + xc, (Ymax / 2) - x + yc, WHITE);
        putpixel(y + (Xmax / 2) + xc, (Ymax / 2) + x + yc, WHITE);
        putpixel(-y + (Xmax / 2) + xc, (Ymax / 2) + x + yc, WHITE);
        x++;
        if (P < 0)
            P += 2 * x + 1;
        else
        {
            y--;
            P += 2 * x - 2 * y + 1;
        }
    }
}
void main()
{
    int r, xc, yc, Xmax, Ymax;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\tc\\BGI");
    clrscr();
    printf("Enter the radius of circle");
    scanf("%d", &r);
    printf("Enter Centre coordinates (xc,yc) : ");
    scanf("%d,%d", &xc, &yc);
    Xmax = getmaxx();
    Ymax = getmaxy();
    line(Xmax / 2, 0, Xmax / 2, Ymax);
    line(0, Ymax / 2, Xmax, Ymax / 2);
    Circle(r, xc, yc);
    getch();
    closegraph();
}