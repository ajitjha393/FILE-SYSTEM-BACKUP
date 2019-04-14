#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

int array[10][2];

int C(int n, int k)
{
    //I used Binomial Theorem
    if (k == 0 || k == n)
        return 1;
    return C(n - 1, k - 1) + C(n - 1, k);
}

float blendingFunction(int n, int k, float u)
{
    return C(n - 1, k) * pow(u, k) * pow(1 - u, n - k - 1);
}

void drawControlPoints(int numOfControlPoints)
{
    for (int i = 0; i < numOfControlPoints - 1; i++)
    {
        setlinestyle(3, 0, 1);
        line(array[i][0], array[i][1], array[i + 1][0], array[i + 1][1]);
    }
}

void beizerCurve(int numOfControlPoints)
{
    float x, y;
    for (float u = 0.001; u <= 1; u += 0.001)
    {
        x = 0.0;
        y = 0.0;
        for (int k = 0; k < numOfControlPoints; k++)
        {
            x += array[k][0] * blendingFunction(numOfControlPoints, k, u);
            y += array[k][1] * blendingFunction(numOfControlPoints, k, u);
        }
        putpixel(x, y, 3);
    }
}

int main()
{

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    int numOfControlPoints;
    cout << "Enter the number of control points : ";
    cin >> numOfControlPoints;
    for (int i = 0; i < numOfControlPoints; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> array[i][j];
        }
    }
    drawControlPoints(numOfControlPoints);
    beizerCurve(numOfControlPoints);
    getch();
    closegraph();
    return 0;
}