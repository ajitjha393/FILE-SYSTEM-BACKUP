#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
void StrokeMethod()
{
    //PRINT B
    line(50, 50, 50, 250);
    delay(500);
    line(50, 50, 100, 100);
    delay(500);
    line(100, 100, 50, 150);
    delay(500);
    line(50, 150, 100, 200);
    delay(500);
    line(100, 200, 50, 250);
    delay(500);

    //PRINT I
    line(150, 60, 250, 60);
    delay(500);
    line(150, 240, 250, 240);
    delay(500);
    line(200, 60, 200, 240);
    delay(500);

    //PRINT S
    line(300, 60, 400, 60);
    delay(500);
    line(300, 60, 300, 160);
    delay(500);
    line(300, 160, 400, 160);
    delay(500);
    line(400, 160, 400, 240);
    delay(500);
    line(400, 240, 280, 240);

    //PRINT U
    line(450, 60, 450, 240);
    delay(500);
    line(550, 60, 550, 240);
    delay(500);
    line(450, 240, 550, 240);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    StrokeMethod();
    getch();
    closegraph();
    return 0;
}