#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
void main()
{
    int g = 0, d;
    initgraph(&g, &d, "C:\\tc\BGI");
    settextstyle(16, 0, 0);
    for (int again = 0; again < 2; again++)
    {
        for (int i = 0, j = 0; i < 360, j < 7200; i++, j += 20)
        {
            delay(50);
            clearviewport();
            int x = 250 * sin(i * 3.14 / 180);
            int y = 170 * cos(i * 3.14 / 180);
            int x1 = 50 * sin(j * 3.14 / 180);
            int y1 = 42 * cos(j * 3.14 / 180);
            int x2 = 25 * sin((j + 60) * 3.14 / 180);
            int y2 = 20 * cos((j + 30) * 3.14 / 180);
            int x3 = 20 * sin((j + 180) * 3.14 / 180);
            int y3 = 10 * cos((j + 240) * 3.14 / 180);
            int x4 = 20 * sin((j + 360) * 3.14 / 180);
            int y4 = 10 * cos((j + 300) * 3.14 / 180);
            int x5 = 20 * sin((j + 30) * 3.14 / 180);
            int y5 = 10 * cos((j + 50) * 3.14 / 180);
            int x6 = 20 * sin((j + 130) * 3.14 / 180);
            int y6 = 10 * cos((j + 150) * 3.14 / 180);
            setcolor(14);
            circle(320, 240, 40); //SUN
            setfillstyle(1, 14);
            floodfill(320, 240, 14);
            setcolor(15);
            ellipse(320, 240, 0, 360, 250, 170); //EARTH ORBIT
            setcolor(8);
            outtextxy(x + x2 + 320, y + y2 + 240, "*"); //SATELLITE
            outtextxy(x + x3 + 320, y + y3 + 240, "*"); //SATELLITE2
            outtextxy(x + x4 + 320, y + y4 + 240, "*"); //SATELLITE3
            setcolor(9);
            circle(x + 320, y + 240, 15); //EARTH
            setfillstyle(1, 9);
            floodfill(x + 320, y + 240, 9);
            setcolor(8);
            outtextxy(x + x5 + 320, y + y5 + 240, "*"); //SATELLITE5
            outtextxy(x + x6 + 320, y + y6 + 240, "*"); //SATELLITE6
            setcolor(7);
            circle(x + x1 + 320, y + y1 + 240, 5); //MOON
            setfillstyle(1, 7);
            floodfill(x + x1 + 320, y + y1 + 240, 7);
        }
    }
}