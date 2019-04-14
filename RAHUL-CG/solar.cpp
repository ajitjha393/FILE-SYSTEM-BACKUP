#include <iostream.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>

void main()
{

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\tc\\BGI");
    for (int again = 0; again < 1; again++)
    {
        for (float i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0, i9 = 0; i1 < 360, i2 < 360, i3 < 360, i4 < 360, i5 < 360, i6 < 360, i7 < 360, i8 < 360, i9 < 360; i1 += 5, i2 += 4, i3 += 3, i4 += 2, i5++, i6 += 0.8, i7 += 0.6, i8 += 0.4, i9 += 0.2)
        {
            delay(20);
            clearviewport();
            setcolor(14);
            circle(320, 240, 40); //SUN
            setfillstyle(1, 14);
            floodfill(320, 240, 14);
            outtextxy(340, 280, "SUN");
            int x = 80 * sin(i1 * 3.14 / 180);
            int y = 52 * cos(i1 * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 80, 52); //ORBIT MERCURY
            setcolor(8);
            circle(x + 320, y + 240, 2); //MERCURY
            outtextxy(x + 324, y + 244, "MERCURY");
            setfillstyle(1, 8);
            floodfill(x + 320, y + 240, 8);
            int x1 = 100 * sin((i2 + 160) * 3.14 / 180);
            int y1 = 62 * cos((i2 + 160) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 100, 60); //ORBIT VENUS
            setcolor(12);
            circle(x1 + 320, y1 + 240, 5); //VENUS
            outtextxy(x1 + 325, y1 + 245, "VENUS");
            setfillstyle(1, 12);
            floodfill(x1 + 320, y1 + 240, 12);
            int x2 = 110 * sin((i3 + 340) * 3.14 / 180);
            int y2 = 72 * cos((i3 + 340) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 110, 72); //ORBIT EARTH
            setcolor(9);
            circle(x2 + 320, y2 + 240, 4); //EARTH
            outtextxy(x2 + 327, y2 + 247, "EARTH");
            setfillstyle(1, 9);
            floodfill(x2 + 320, y2 + 240, 9);
            int x3 = 120 * sin((i4 + 20) * 3.14 / 180);
            int y3 = 82 * cos((i4 + 20) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 120, 82); //ORBIT MARS
            setcolor(4);
            circle(x3 + 320, y3 + 240, 3); //MARS
            outtextxy(x3 + 328, y3 + 248, "MARS");
            setfillstyle(1, 4);
            floodfill(x3 + 320, y3 + 240, 4);
            for (int k1 = 0; k1 < 1000; k1 += 4)
            {
                int x10 = 160 * sin(k1 * 3.14 / 180);
                int y10 = 112 * cos(k1 * 3.14 / 180);
                putpixel(x10 + 320, y10 + 240, 15); //ASTROIDS
                putpixel(x10 + 321, y10 + 241, 15);
                putpixel(x10 + 319, y10 + 239, 15);
                putpixel(x10 + 322, y10 + 242, 15);
            }
            int x4 = 180 * sin((i5 + 90) * 3.14 / 180);
            int y4 = 142 * cos((i5 + 90) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 180, 142); //ORBIT JUPITER
            setcolor(12);
            circle(x4 + 320, y4 + 240, 10); //JUPTIER
            outtextxy(x4 + 328, y4 + 248, "JUPITER");
            setfillstyle(1, 12);
            floodfill(x4 + 320, y4 + 240, 12);
            int x5 = 205 * sin((i6 + 280) * 3.14 / 180);
            int y5 = 172 * cos((i6 + 280) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 205, 172); //ORBIT SATURN
            setcolor(9);
            ellipse(x5 + 320, y5 + 240, 0, 360, 10, 4); //SATURN RINGS
            setcolor(1);
            circle(x5 + 320, y5 + 240, 8); //SATURN
            outtextxy(x5 + 328, y5 + 248, "SATURN");
            setfillstyle(1, 1);
            floodfill(x5 + 320, y5 + 240, 1);
            int x6 = 230 * sin((i7 + 280) * 3.14 / 180);
            int y6 = 212 * cos((i7 + 280) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 230, 212); //ORBIT URANUS
            setcolor(7);
            circle(x6 + 320, y6 + 240, 6); //URANUS
            outtextxy(x6 + 326, y6 + 246, "URANUS");
            setfillstyle(1, 7);
            floodfill(x6 + 320, y6 + 240, 7);
            int x7 = 260 * sin((i8 + 200) * 3.14 / 180);
            int y7 = 235 * cos((i8 + 200) * 3.14 / 180);
            setcolor(15);
            ellipse(320, 240, 0, 360, 260, 235); //ORBIT NEPTUNE
            setcolor(3);
            circle(x7 + 320, y7 + 240, 5); //NEPTUNE
            outtextxy(x7 + 326, y7 + 246, "NEPTUNE");
            setfillstyle(1, 3);
            floodfill(x7 + 320, y7 + 240, 3);
            for (int k = 0; k < 1000; k++)
            {
                int x9 = 300 * sin((k + 8) * 3.14 / 180);
                int y9 = 225 * cos(k * 3.14 / 180);
                putpixel(x9 + 320, y9 + 240, 15); //ORBIT PLUTO
            }
            int x8 = 300 * sin((i9 + 8) * 3.14 / 180);
            int y8 = 225 * cos(i9 * 3.14 / 180);
            setcolor(8);
            circle(x8 + 320, y8 + 240, 2); //PLUTO
            outtextxy(x8 + 326, y8 + 246, "PLUTO");
            setfillstyle(1, 8);
            floodfill(x8 + 320, y8 + 240, 8);
        }
    }
}