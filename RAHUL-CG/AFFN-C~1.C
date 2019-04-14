#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>

void circ(int Xc, int Yc, int r)
{
    int Pi, i, Xi, Yi;
    Pi = 1 - r;
    //Iski Zarurat nhi hai Isliye hi error aa rha hai
    Xi = 0; //Xi = 320;
    Yi = r; // Yi = r + 240;

    while (Xi <= Yi)
    {

        //PUTPIXEL IF KE BAHAR LIKHNA HAI
        putpixel(Xi + Xc, Yi + Yc, WHITE);
        putpixel(Yi + Xc, Xi + Yc, WHITE);
        putpixel(Yi + Xc, -Xi + Yc, WHITE);
        putpixel(Xi + Xc, -Yi + Yc, WHITE);
        putpixel(-Xi + Xc, -Yi + Yc, WHITE);
        putpixel(-Yi + Xc, -Xi + Yc, WHITE);
        putpixel(-Yi + Xc, Xi + Yc, WHITE);
        putpixel(-Xi + Xc, Yi + Yc, WHITE);
        if (Pi < 0)
        {
            Xi = Xi + 1;

            Pi = Pi + (2 * Xi) + 1; //Yahan pe tune 2(x+1) + 1 likha tha yeh error tha (sirf 2*x +1 aayega)
        }
        else
        {
            Xi = Xi + 1;
            Yi = Yi - 1;

            Pi = Pi + (2 * Xi) - (2 * (Yi)) + 1; //Yaha sirf 2x - 2y + 1 likhna hai because x+1 and y-1 upar hi kaar liya hai
        }
    }
}

void main()
{
    int gd = DETECT, gm;
    int xc,yc,r;
    initgraph(&gd, &gm, "C:\\tc\\BGI"); //This is path of my Pc

    printf("Enter the radius of circle");
    scanf("%d", &r);
    printf("Enter Centre coordinates (xc,yc) : ");
    scanf("%d%d", &xc, &yc);
    circ(xc, yc, r);
    getch();

    getch();
    closegraph();
}
