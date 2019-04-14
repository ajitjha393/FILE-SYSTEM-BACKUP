#include <iostream.h>
#include <dos.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
void base()
{ //To draw the lines along X and Y axis
    int x, y;
    char ch;
    x = getmaxx() - 2;
    y = getmaxy() / 2;
    line(1, 1, 1, 2 * y);
    line(1, y, x, y);
}

// Initial method used by me - Even this works//

//P = 1 + x/1 + x^2/2! + x^3/3!

/*I Was so stupid to use Taylor series as a decision parameter for Making sine and cosine curve When I had sine function to calculate the value */

/*This is VERSION 2.0 of Making curves
U can extend this idea and make curve for tan,cot,log,etc.
So plz use ur imgination :) */

void s_sin()
{

    //putpixel(xx,yy,RED);
    float xx = 1, a = 100;
    float th = 0, y, yy = y = getmaxy() / 2;
    char ch;
    setcolor(CYAN);
    outtextxy(270, 30, "Sin Curve");
    while (1)
    {
        yy = y - a * sin(th); //to draw sin curve line
        xx += 1;
        th = th + 22.0 / 7 * 30;
        putpixel(xx, yy, WHITE);
        delay(30);
        if (kbhit()) //exit when we press esc
        {
            ch = getch();
            if (ch == 27)
                return;
        }
    }
}
void s_cos()
{
    int xx = 1, a = 100;
    float th = 0, y, yy = y = getmaxy() / 2;
    char ch;
    setcolor(CYAN);
    outtextxy(270, 30, "Cos Curve");
    while (1)
    {
        yy = y - a * cos(th); //formula to draw cos curve line
        xx += 1.0;
        th = th + 22.0 / 7 * 30;
        putpixel(xx, yy, WHITE);
        delay(30);
        if (kbhit())
        {
            ch = getch();
            if (ch == 27) //exit when we press esc
                return;
        }
    }
}

void main()
{
    int gd = DETECT, gm;
    char ch;
    initgraph(&gd, &gm, "C:\\tc\\BGI");
    settextstyle(4, 0, 12);
    outtextxy(120, 30, "Curves");
    settextstyle(1, 0, 3);
    outtextxy(200, 200, "1. Press S for sin wave");
    settextstyle(1, 0, 3);
    outtextxy(200, 220, "2. Press c for cos wave");
    ch = getch();
    cleardevice();
    switch (ch)
    {
    case 's':
    case 'S':
        base();
        s_sin();
        break;
    case 'c':
    case 'C':
        base();
        s_cos();
        break;
    }
    getch();
    closegraph();
}