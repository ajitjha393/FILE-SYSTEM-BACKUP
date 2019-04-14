#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy;
    putpixel(x1, y1, WHITE);
    dx = abs(x1 - x2);
    dy = abs(y1 - y2);
    int s1, s2, temp, P, flag = 0, i;

    if (x2 - x1 < 0)
        s1 = -1;
    else if (x2 - x1 > 0)
        s1 = 1;
    else
        s1 = 0;

    if (y2 - y1 < 0)
        s2 = -1;
    else if (y2 - y1 > 0)
        s2 = 1;
    else
        s2 = 0;

    if (dy > dx)
    {
        temp = dy;
        dy = dx;
        dx = temp;
        flag = 1;
    }

    P = (2 * dy) - dx;

    for (i = 0; i < dx; i++)
    {
        if (P < 0)
        {
            if (flag == 1)
            {
                x1 = x1;
                y1 = y1 + s2;
                putpixel(x1, y1, WHITE);
                P = P + (2 * dy);
            }
            else
            {
                x1 = x1 + s1;
                y1 = y1;
                putpixel(x1, y1, WHITE);
                P = P + (2 * dy);
            }
        }
        else
        {
            if (P >= 0)
            {
                x1 = x1 + s1;
                y1 = y1 + s2;
                putpixel(x1, y1, WHITE);
                P = P + (2 * dy) - (2 * dx);
            }
        }
    }
}
void drawCircle(int radius, int Xc, int Yc)
{
    int X = 0, Y = 0, i, P;
    //	printf("Enter the radius of the circle and circle center");
    //	scanf("%d%d%d",&radius,&Xc,&Yc);
    putpixel(Xc + 0, Yc + radius, WHITE);
    putpixel(Xc + radius, Yc + 0, WHITE);
    putpixel(Xc + 0, (-radius + Yc), WHITE);
    putpixel((-radius + Xc), Yc + 0, WHITE);
    P = 1 - radius;
    Y = radius;
    for (i = 0; X <= Y; i++)
    {
        if (P < 0)
        {
            X = X + 1;
            putpixel(X + Xc, Y + Yc, WHITE);
            putpixel(X + Xc, (-Y + Yc), WHITE);
            putpixel((-X + Xc), Y + Yc, WHITE);
            putpixel((-X + Xc), (-Y + Yc), WHITE);
            putpixel(Y + Xc, X + Yc, WHITE);
            putpixel(Y + Xc, (-X + Yc), WHITE);
            putpixel((-Y + Xc), X + Yc, WHITE);
            putpixel((-Y + Xc), (-X + Yc), WHITE);
            P = P + (2 * X) + 1;
        }
        else
        {
            X = X + 1;
            Y = Y - 1;
            putpixel(X + Xc, Y + Yc, WHITE);
            putpixel(X + Xc, (-Y + Yc), WHITE);
            putpixel((-X + Xc), Y + Yc, WHITE);
            putpixel((-X + Xc), (-Y + Yc), WHITE);
            putpixel(Y + Xc, X + Yc, WHITE);
            putpixel(Y + Xc, (-X + Yc), WHITE);
            putpixel((-Y + Xc), X + Yc, WHITE);
            putpixel((-Y + Xc), (-X + Yc), WHITE);
            P = P + (2 * X) - (2 * Y);
        }
    }
}
void floodFill(int a, int b, int fillColor, int interiorColor)
{
    if (getpixel(a, b) == interiorColor)
    {
        putpixel(a, b, fillColor);
        floodFill(a - 1, b, fillColor, interiorColor);
        floodFill(a, b - 1, fillColor, interiorColor);
        floodFill(a + 1, b - 1, fillColor, interiorColor);
        floodFill(a, b + 1, fillColor, interiorColor);
    }
}
void boundaryfill(int x, int y, int fillColor, int boundaryColor)
{
    if (getpixel(x, y) != boundaryColor && getpixel(x, y) != fillColor)
    {
        putpixel(x, y, fillColor);
        boundaryfill(x, y - 1, fillColor, boundaryColor);
        boundaryfill(x, y + 1, fillColor, boundaryColor);
        boundaryfill(x - 1, y, fillColor, boundaryColor);
        boundaryfill(x + 1, y, fillColor, boundaryColor);
    }
}
void main()
{
    int gd = DETECT, gm, i, j = 0, p;
    initgraph(&gd, &gm, "C://TC//BGI");
    int cond1, cond2;
    for (int p = 0; p <= 1; p++)
    {
        //FOR TRAFFIC SIGNAL
        for (j = 0; j <= 2; j++)
        {
            //FOR CIRCLE WITH 3 COLORS
            //FOR RED
            if (j == 0)
            {

                i = (p == 0) ? 0 : 200;
                bresenham(0, 390, 639, 390); //ROAD

                //CAR BODY
                bresenham(50 + i, 370, 90 + i, 370);
                arc(110 + i, 370, 0, 180, 20);
                bresenham(130 + i, 370, 220 + i, 370);
                arc(240 + i, 370, 0, 180, 20);
                bresenham(260 + i, 370, 300 + i, 370);
                bresenham(300 + i, 370, 300 + i, 350);
                bresenham(300 + i, 350, 240 + i, 330);
                bresenham(240 + i, 330, 200 + i, 300);
                bresenham(200 + i, 300, 110 + i, 300);
                bresenham(110 + i, 300, 80 + i, 330);
                bresenham(80 + i, 330, 50 + i, 340);
                bresenham(50 + i, 340, 50 + i, 370);

                //CAR WINDOW
                bresenham(165 + i, 305, 165 + i, 330);
                bresenham(165 + i, 330, 230 + i, 330);
                bresenham(230 + i, 330, 195 + i, 305);
                bresenham(195 + i, 305, 165 + i, 305);

                bresenham(160 + i, 305, 160 + i, 330);
                bresenham(160 + i, 330, 95 + i, 330);
                bresenham(95 + i, 330, 120 + i, 305);
                bresenham(120 + i, 305, 160 + i, 305);

                //WHEELS
                drawCircle(17, 110 + i, 370);
                drawCircle(17, 240 + i, 370);
                //FOR TRAFFIC SIGNAL
                bresenham(500, 75, 500, 185);
                arc(540, 75, 0, 180, 40);
                bresenham(580, 75, 580, 185);
                arc(540, 185, 180, 360, 40);
                drawCircle(20, 540, 75);
                boundaryfill(540, 75, RED, WHITE);

                delay(2000);
            }
            //FOR YELLOW
            if (j == 1)
            {

                cond1 = (p == 0) ? 50 : 250;
                i = (p == 0) ? 0 : 200;

                for (; i < cond1; i += 2)
                {
                    //FOR TRAFFIC SIGNAL

                    bresenham(0, 390, 639, 390); //ROAD

                    //CAR BODY
                    bresenham(50 + i, 370, 90 + i, 370);
                    arc(110 + i, 370, 0, 180, 20);
                    bresenham(130 + i, 370, 220 + i, 370);
                    arc(240 + i, 370, 0, 180, 20);
                    bresenham(260 + i, 370, 300 + i, 370);
                    bresenham(300 + i, 370, 300 + i, 350);
                    bresenham(300 + i, 350, 240 + i, 330);
                    bresenham(240 + i, 330, 200 + i, 300);
                    bresenham(200 + i, 300, 110 + i, 300);
                    bresenham(110 + i, 300, 80 + i, 330);
                    bresenham(80 + i, 330, 50 + i, 340);
                    bresenham(50 + i, 340, 50 + i, 370);

                    //CAR WINDOW
                    bresenham(165 + i, 305, 165 + i, 330);
                    bresenham(165 + i, 330, 230 + i, 330);
                    bresenham(230 + i, 330, 195 + i, 305);
                    bresenham(195 + i, 305, 165 + i, 305);

                    bresenham(160 + i, 305, 160 + i, 330);
                    bresenham(160 + i, 330, 95 + i, 330);
                    bresenham(95 + i, 330, 120 + i, 305);
                    bresenham(120 + i, 305, 160 + i, 305);

                    //WHEELS
                    drawCircle(17, 110 + i, 370);
                    drawCircle(17, 240 + i, 370);
                    bresenham(500, 75, 500, 185);
                    arc(540, 75, 0, 180, 40);
                    bresenham(580, 75, 580, 185);
                    arc(540, 185, 180, 360, 40);

                    drawCircle(20, 540, 135);
                    boundaryfill(540, 135, YELLOW, WHITE);
                    //delay(500);

                    delay(8);
                    cleardevice();
                }
            }

            //FOR GREEN
            if (j == 2)
            {

                cond1 = (p == 0) ? 200 : 500;
                i = (p == 0) ? 50 : 250;

                //drawCircle(20, 540, 195);
                for (; i < cond1; i += 10)
                {

                    //delay(500);
                    bresenham(0, 390, 639, 390); //ROAD

                    //CAR BODY
                    bresenham(50 + i, 370, 90 + i, 370);
                    arc(110 + i, 370, 0, 180, 20);
                    bresenham(130 + i, 370, 220 + i, 370);
                    arc(240 + i, 370, 0, 180, 20);
                    bresenham(260 + i, 370, 300 + i, 370);
                    bresenham(300 + i, 370, 300 + i, 350);
                    bresenham(300 + i, 350, 240 + i, 330);
                    bresenham(240 + i, 330, 200 + i, 300);
                    bresenham(200 + i, 300, 110 + i, 300);
                    bresenham(110 + i, 300, 80 + i, 330);
                    bresenham(80 + i, 330, 50 + i, 340);
                    bresenham(50 + i, 340, 50 + i, 370);

                    //CAR WINDOW
                    bresenham(165 + i, 305, 165 + i, 330);
                    bresenham(165 + i, 330, 230 + i, 330);
                    bresenham(230 + i, 330, 195 + i, 305);
                    bresenham(195 + i, 305, 165 + i, 305);

                    bresenham(160 + i, 305, 160 + i, 330);
                    bresenham(160 + i, 330, 95 + i, 330);
                    bresenham(95 + i, 330, 120 + i, 305);
                    bresenham(120 + i, 305, 160 + i, 305);

                    //WHEELS
                    drawCircle(17, 110 + i, 370);
                    drawCircle(17, 240 + i, 370);

                    //delay(500);
                    bresenham(500, 75, 500, 185);
                    arc(540, 75, 0, 180, 40);
                    bresenham(580, 75, 580, 185);
                    arc(540, 185, 180, 360, 40);

                    drawCircle(20, 540, 195);
                    boundaryfill(540, 195, GREEN, WHITE);
                    delay(2);
                    cleardevice();
                }
            }
            //	delay(100);
            //	delay();
            cleardevice();
        }
    }
    getch();
    closegraph();
}