
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void printSymmetry(float x, float y, float xc, float yc)
{

    putpixel(x + xc, y + yc, WHITE);
    putpixel(-x + xc, y + yc, WHITE);
    putpixel(x + xc, -y + yc, WHITE);
    putpixel(-x + xc, -y + yc, WHITE);
}

void Ellipse(float rx, float ry, float xc, float yc)
{

    float p;
    float x = 0, y = ry;
    printSymmetry(x, y, xc, yc);

    p = (ry * ry) - ((rx * rx) * (ry)) + ((0.25) * (rx * rx));

    do
    {
        x++;
        if (p < 0)
        {

            printSymmetry(x, y, xc, yc);
            p += (2 * (ry * ry) * x) + (ry * ry);
        }
        else
        {
            y--;
            printSymmetry(x, y, xc, yc);
            p += (2 * (ry * ry) * x) + (ry * ry) - (2 * (rx * rx) * y);
        }

    } while ((ry * ry * x) <= (rx * rx * y));

    //For region R2

    p = ((ry * ry) * (x + 0.5) * (x + 0.5)) + ((rx * rx) * (y - 1) * (y - 1)) - (rx * rx * ry * ry);

    do
    {
        y--;
        if (p < 0)
        {
            x++;
            printSymmetry(x, y, xc, yc);
            p += 2 * (ry * ry) * x - 2 * (rx * rx) * y + rx * rx;
        }
        else
        {

            printSymmetry(x, y, xc, yc);
            p = p + (-2 * (rx * rx) * y) + (rx * rx);
        }

    } while ((y >= 0));
}

void main()
{
    int rx, ry, xc, yc, Xmax, Ymax;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\tc\\BGI");

    clrscr();
    printf("Enter the radius of ellipse about x-axis");
    scanf("%d", &rx);
    printf("Enter the radius of ellipse about y-axis");
    scanf("%d", &ry);
    printf("Enter Centre coordinates (xc,yc) : ");
    scanf("%d,%d", &xc, &yc);
    Ellipse(rx, ry, xc, yc);
    Xmax = getmaxx();
    Ymax = getmaxy();

    getch();
    closegraph();
}