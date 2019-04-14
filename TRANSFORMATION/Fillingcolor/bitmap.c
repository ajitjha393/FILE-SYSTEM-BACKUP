#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void bitMap()
{
    int i, j;
    int row = 200;
    int col = 50;
    int myNameMap[200][50] = {0};
    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 50; j++)
        {
            if (j == 0)
                myNameMap[i][j] = 1;
            else if ((i < 50 && i == j) || (i >= 100 && i <= 150 && i == j + 100))
                myNameMap[i][j] = 1;
            else if (i >= 50 && i < 100)
                myNameMap[i][100 - i] = 1;
            else if (i >= 150 && i < 200)
                myNameMap[i][200 - i] = 1;
        }
    }

    for (i = 0; i < 200; i++)
        for (j = 0; j < 50; j++)
        {
            if (myNameMap[i][j] == 1)
            {
                putpixel(200 + j, 100 + i, 3);
            }
        }
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    bitMap();
    getch();
    closegraph();
    return 0;
}