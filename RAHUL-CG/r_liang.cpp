#include <stdio.h>
#include <conio.h>
#include <graphics.h>
int arr[] = {100, 100, 400, 100, 400, 400, 100, 400, 100, 100};
void liangBLine()
{
    int X1, Y1, X2, Y2, P[4], Q[4], i, j, k;
    float first[4], second[4], max, min, XX1, YY1, XX2, YY2, t1, t2; //made t1,t2 float
    printf(" Enter the co-ordinates of the line ");
    scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    line(X1, Y1, X2, Y2);
    getch();
    cleardevice();
    drawpoly(5, arr);

    P[0] = -(X2 - X1);
    P[1] = (X2 - X1);
    P[2] = -(Y2 - Y1);
    P[3] = (Y2 - Y1);
    Q[0] = X1 - 100;
    Q[1] = 400 - X1;
    Q[2] = Y1 - 100;
    Q[3] = 400 - Y1;
    for (i = 0; i < 4; i++)
    {
        if (P[i] == 0)
        {
            printf(" Line is parallel to the clipping boundary ");
            if (Q[i] < 0)
            {
                printf("Line is completely outside the boundary ");
                return;
            }
            else
            {
                if (P[1] == 0)
                {
                    printf("Line is vertical\n");
                    if (Y1 < 100 && Y2 < 400)
                    {
                        line(X1, 100, X2, Y2);
                    }
                    else if (Y1 > 100 && Y2 < 400)
                    {
                        line(X1, Y1, X2, Y2);
                    }
                    else
                    {
                        line(X1, Y1, X2, 400);
                    }
                }
                if (P[3] == 0)
                {
                    printf("Line is horizontal");
                    if (X1 < 100 && X2 < 400)
                    {
                        line(100, Y1, X2, Y2);
                    }
                    else if (X1 > 100 && X2 < 400)
                    {
                        line(X1, Y1, X2, Y2);
                    }
                    else
                    {
                        line(X1, Y1, 400, Y2);
                    }
                }
            }
        }
    }
    //Here there was problem u have to use separate for loop for finding parameter or else after every iteration u will get different t1 and t2 as everytime t1 =0 t2 = 1 at start

    t1 = 0;
    t2 = 1;
    //Write these initializations outside
    j = 0;
    first[j] = 0;
    k = 0;
    second[k] = 1;

    for (i = 0; i < 4; i++)
    {
        if (P[i] < 0)
        {
            first[++j] = (float)Q[i] / P[i];
        }
        else
        {
            second[++k] = (float)Q[i] / P[i];
        }
    }

    max = first[0];
    min = second[0];
    for (i = 1; i <= j; i++)
    {
        if (first[i] > max)
        {
            max = first[i];
        }
    }
    for (i = 1; i <= k; i++)
    {
        if (second[i] < min)
        {
            min = second[i];
        }
    }

    t1 = max;
    t2 = min;
    if (t1 < t2)
    {
        XX1 = X1 + (t1 * (X2 - X1));
        XX2 = X1 + (t2 * (X2 - X1));
        YY1 = Y1 + (t1 * (Y2 - Y1));
        YY2 = Y1 + (t2 * (Y2 - Y1));
        line(int(XX1), int(YY1), int(XX2), int(YY2));
    }
}
void main()
{
    int gd = DETECT, gm;
    int i, j;
    initgraph(&gd, &gm, "\\BGI");

    drawpoly(5, arr);
    liangBLine();
    getch();
    closegraph();
}