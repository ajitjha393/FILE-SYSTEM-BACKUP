#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#define pi 3.14
void translation(int[], int[], int);
void rotation(int[], int[], int);
void scaling(int[], int[], int);
void reflection(int[], int[], int);
void shearing(int[], int[], int);
void multMatrix(int[20][20], int[20][20], int);
void RotMultMatrix(float matrix[20][20], float rot[20][20], int n);
//I made this to Draw axes//

void drawAxes()
{
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
}
void main()
{
    int gd = DETECT, gm, i, n, j, k, ch;
    int x[20], y[20];
    initgraph(&gd, &gm, "C:\\TC\\BGI"); //"C://TURBOC3//BGI"
    printf("\nEnter the number of edges: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the coordinates: ");
        scanf("%d %d", &x[i], &y[i]);
    }
    drawAxes(); //Changed this
    printf("\n1.TRANSLATION\n2.ROTATION\n3.SCALING\n4.REFLECTION\n5.SHEARING");
    printf("\nEnter your choice: ");
    scanf("%d", &ch);

    /*
    Bro see we know that whatever transformation matrix we had derive works only when object is at origin but we know that it is not hence we translate our axes into origin at(320,240)
    */
    for (i = 0; i < n - 1; i++)
    {
        line(320 + x[i], 240 - y[i], 320 + x[i + 1], 240 - y[i + 1]); //changed this
    }
    line(320 + x[i], 240 - y[i], 320 + x[0], 240 - y[0]); // changed this
    if (ch == 1)
        translation(x, y, n);
    else if (ch == 2)
        rotation(x, y, n);
    else if (ch == 3)
        scaling(x, y, n);
    else if (ch == 4)
        reflection(x, y, n);
    else if (ch == 5)
        shearing(x, y, n);
    else
        printf("\nInvalid choice");

    getch();
    cleardevice();
    closegraph();
}

void translation(int x[], int y[], int n)
{
    int matrix[20][20], j, rx, ry, k, trans[20][20];
    for (j = 0; j < n; j++)
    {
        matrix[j][0] = x[j];
        matrix[j][1] = y[j];
        matrix[j][2] = 1;
    }
    printf("\nEnter the horizontal distance to be shifted: ");
    scanf("%d", &rx);
    printf("\nEnter the vertical distance to be shifted: ");
    scanf("%d", &ry);
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {

            if (j == k)
                trans[j][k] = 1;
            else if (j == 2)
            {
                trans[j][0] = rx;
                trans[j][1] = ry;
            }
            else
            {
                trans[j][k] = 0;
            }
        }
    }
    multMatrix(matrix, trans, n);
}

void rotation(int x[], int y[], int n)
{
    //Since rotation involves float matrix we will use another multiplication function//
    float matrix[20][20], rot[20][20], k;
    float o, th;
    int j;
    for (j = 0; j < n; j++)
    {
        matrix[j][0] = x[j];
        matrix[j][1] = y[j];
        matrix[j][2] = 1;
    }
    printf("\nEnter the angle by which shape is to be rotated in degrees: ");
    scanf("%f", &o);
    th = (o * pi) / 180;
    //If u will do int u will get all 0 because cos ranges from 0 to 1 and int of (0.xxx) will be 0 only
    rot[0][0] = cos(th);
    rot[0][1] = sin(th);
    rot[0][2] = 0;
    rot[1][0] = -sin(th);
    rot[1][1] = cos(th);
    rot[1][2] = 0;

    rot[2][0] = 0;
    rot[2][1] = 0;
    rot[2][2] = 1;
    RotMultMatrix(matrix, rot, n);
}
void scaling(int x[], int y[], int n)
{
    int matrix[20][20], j, scale[20][20], k, sx, sy;
    for (j = 0; j < n; j++)
    {
        matrix[j][0] = x[j];
        matrix[j][1] = y[j];
        matrix[j][2] = 1;
    }
    printf("\nEnter the scaling factor in x: ");
    scanf("%d", &sx);
    printf("\nEnter the scaling factor in y: ");
    scanf("%d", &sy);
    scale[2][2] = 1;
    scale[0][0] = sx;
    scale[1][1] = sy;
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {
            if (j != k)
                scale[j][k] = 0;
        }
    }
    multMatrix(matrix, scale, n);
}
void reflection(int x[], int y[], int n)
{
    int matrix[20][20], j, ref[20][20], k;
    for (j = 0; j < n; j++)

    {
        matrix[j][0] = x[j];
        matrix[j][1] = y[j];
        matrix[j][2] = 1;
    }
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {
            if (j != k)
                ref[j][k] = 0;
            else if (j == k && j == 1)
                ref[j][k] = -1;
            else if (j == k && j != 1)
                ref[j][k] = 1;
        }
    }
    multMatrix(matrix, ref, n);
}
void shearing(int x[], int y[], int n)
{
    int matrix[20][20], j, ref[20][20], k, shear[20][20], shx;
    for (j = 0; j < n; j++)
    {
        matrix[j][0] = x[j];
        matrix[j][1] = y[j];
        matrix[j][2] = 1;
    }
    printf("\nEnter the shearing factor in x direction: ");
    scanf("%d", &shx);
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {
            if (j == k)

                shear[j][k] = 1;
            else
                shear[j][k] = 0;
        }
    }
    shear[1][0] = shx;
    multMatrix(matrix, shear, n);
}
//CREATED NEW FUNCTION
void RotMultMatrix(float matrix[20][20], float trans[20][20], int n)
{
    float c[20][20];
    int i, j, k, m = 0, l = 0;
    float sum = 0.0;
    int x[20], y[20];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 3; k++)
            {
                sum = sum + (matrix[i][k] * trans[k][j]);
            }
            c[i][j] = sum;
            sum = 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j == 0)
                x[l++] = c[i][j];
            else if (j == 1)
                y[m++] = c[i][j];
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        line(320 + x[i], 240 - y[i], 320 + x[i + 1], 240 - y[i + 1]);
    }
    line(320 + x[i], 240 - y[i], 320 + x[0], 240 - y[0]);
}

void multMatrix(int matrix[20][20], int trans[20][20], int n)
{
    int c[20][20];
    int i, j, k, sum = 0, m = 0, l = 0;
    int x[20], y[20];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 3; k++)
            {
                sum = sum + (matrix[i][k] * trans[k][j]);
            }
            c[i][j] = sum;
            sum = 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j == 0)
                x[l++] = c[i][j];
            else if (j == 1)
                y[m++] = c[i][j];
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        line(320 + x[i], 240 - y[i], 320 + x[i + 1], 240 - y[i + 1]); //Changed this
    }
    line(320 + x[i], 240 - y[i], 320 + x[0], 240 - y[0]); //Changed this
}