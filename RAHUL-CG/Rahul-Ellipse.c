#include <stdio.h>
#include <conio.h>
#include <graphics.h>

//This is my method which  to print symmetry point to avoid writing putpixel again and again
void printSymmetry(float X, float Y, float Xc, float Yc)
{

    putpixel(X + Xc, Y + Yc, WHITE);
    putpixel(-X + Xc, Y + Yc, WHITE);
    putpixel(X + Xc, -Y + Yc, WHITE);
    putpixel(-X + Xc, -Y + Yc, WHITE);
}

void drawEllipse()
{
    float Rx, Ry, Xc, Yc, i, P1, P2, X, Y;
    printf("Enter Rx,Ry and centre Xc,Yc");
    scanf("%f%f%f%f", &Rx, &Ry, &Xc, &Yc);
    X = 0.0; //Use 0.0 as it is float variable
    Y = Ry;
    P1 = (Ry * Ry) - (Rx * Rx * Ry) + (0.25 * Rx * Rx);
    printSymmetry(X, Y, Xc, Yc);
    /*Code will work fine with this also  but it is not tidy*/
    // putpixel(0 + Xc, Ry + Yc, WHITE);
    // putpixel(Ry + Xc, 0 + Yc, WHITE);
    // putpixel(0 + Xc, -Ry + Yc, WHITE);
    // putpixel(-Ry + Xc, 0 + Yc, WHITE);
    //
    do
    {
        if (P1 < 0)
        {
            X = X + 1;
            printSymmetry(X, Y, Xc, Yc);
            P1 = P1 + (2 * Ry * Ry * X) + (Ry * Ry);
        }
        else
        {
            X = X + 1;
            Y = Y - 1;
            printSymmetry(X, Y, Xc, Yc);
            P1 = P1 + (2 * Ry * Ry * X) - (2 * Rx * Rx * Y) + (Ry * Ry);
        }
    } while ((2 * Ry * Ry * X) <= (2 * Rx * Rx * Y));

    //This was the main mistake u were again initialzing it to region1
    // X = 0;
    // Y = Ry;
    P2 = (Ry * Ry) * (X + 0.5) * (X + 0.5) + (Rx * Rx * (Y - 1) * (Y - 1)) - (Rx * Rx * Ry * Ry);
    do
    {
        if (P2 < 0)
        {
            X = X + 1;
            Y = Y - 1;
            printSymmetry(X, Y, Xc, Yc);
            P2 = P2 + (2 * Ry * Ry * X) - (2 * Rx * Rx * Y) + (Rx * Rx);
        }
        else
        {
            Y = Y - 1;
            printSymmetry(X, Y, Xc, Yc);
            P2 = P2 - (2 * Rx * Rx * Y) + (Rx * Rx);
        }
    } while (Y >= 0);
}
void main()
{
    int gd = DETECT, gm;
    clrscr();
    initgraph(&gd, &gm, "C:\\tc\\BGI"); ///I replaced this as my tc path "C:\\tc\\BGI"
    drawEllipse();
    getch();
    closegraph();
}
