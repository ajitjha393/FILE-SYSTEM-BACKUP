#include <iostream.h>
#include <process.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#define pi 3.1427
int x[30], y[30];
void star();
void pttrn();
void pttrn1();
int gd = DETECT, gm, r, xc, yc, n;
void main()
{
    initgraph(&gd, &gm, "C:\\tc\\BGI"); // initallizing graphics
    cleardevice();
    cout << "enter the radius ";
    cin >> r;
    cout << "enter centre ";
    cin >> xc >> yc;
    cout << "enter the number of points ";
    cin >> n;
    cleardevice();
    gotoxy(32, 1);
    cout << "ROSETTE STRUCTURE";
    gotoxy(53, 30);
    cout << " DEVELOPED BY: AJAY KUMAR";
    star();
    pttrn();
    getch();
    cleardevice();
    pttrn1();
    getch();
    closegraph();
}
void star()
{ //just to print the colored dots in background
    int MaxX = getmaxx(), MaxY = getmaxy(), i;
    for (i = 0; i < 2024; i++)
        putpixel(random; (MaxX), random(MaxY), random(15));
}
void pttrn()
{
    int i, j;
    //initgraph(&gd,&gm,"");                 //to find the points on circle
    for (i = 0; i < n; i++)
    {
        x[i] = r * cos((2 * pi * i) / n) + xc;
        y[i] = r * sin((2 * pi * i) / n) + yc;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            setcolor(j);
            line(x[i], y[i], x[j], y[j]); //to draw line from each point
            delay(30);
        }
    }
}
void pttrn1()
{
    int k = 0, i, j, l = 0;
    while (!kbhit())
    {
        cleardevice();
        star();
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                setcolor(l);
                l++;
                line(x[i] + k, y[i], x[j] + k, y[j]); // during movment from left to right, darwing of line and changing color of lines
                if (((x[i] + k) >= getmaxx()))
                {
                    x[i] = -k;
                }
            }
        }
        k++;
    }
}
