#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#define N 20
#define pi 3.142

void drawPolygon(int numOfVertices, int arr[], int color)
{
    setcolor(color);
    for (int i = 0; i <= numOfVertices; i += 2)
        line(arr[i] + (getmaxx() / 2), (getmaxy() / 2) - arr[i + 1], arr[i + 2] + (getmaxx() / 2), (getmaxy() / 2) - arr[i + 3]);

    line(arr[i] + (getmaxx() / 2), (getmaxy() / 2) - arr[i + 1], (getmaxx() / 2) + arr[0], (getmaxy() / 2) - arr[1]);
    setcolor(WHITE);
}
void drawAxes()
{
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
}

void Input(int array[], int numOfVertices)
{
    cout << "Enter the x y value of the vertices of polygon : " << endl;
    int i;
    for (i = 0; i < 2 * numOfVertices; i++)
    {
        cin >> array[i];
    }

    array[i++] = array[0];
    array[i] = array[1];
}
void formCoordinateMatrix(int array[], int myVerticesMatrix[][N], int numOfVertices)
{
    int k = 0;
    for (int i = 0; i < numOfVertices; i++)
        for (int j = 0; j < 3; j++)
        {
            if (j == 2)
                myVerticesMatrix[i][j] = 1;
            else
            {
                myVerticesMatrix[i][j] = array[k++];
            }
        }
}

void findTransformedMatrix(int newMatrix[][N], int myVerticesMatrix[][N], float ScalingMatrix[][N], int numOfVertices)
{
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = 0;
            for (int k = 0; k < 3; k++)
                newMatrix[i][j] += myVerticesMatrix[i][k] * ScalingMatrix[k][j];
        }
    }
}

void createArrayFromMatrix(int newMatrix[][N], int myArray[], int numOfVertices)
{
    int k = 0;
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            myArray[k++] = newMatrix[i][j];
        }
    }
    myArray[k++] = myArray[0];
    myArray[k] = myArray[1];
}

void formScalingMatrix(float ScalingMatrix[][N], int Sx, int Sy)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ScalingMatrix[i][j] = 0;

    ScalingMatrix[0][0] = Sx;
    ScalingMatrix[1][1] = Sy;
    ScalingMatrix[2][2] = 1;
}

void SCALE(int myVerticesMatrix[][N], float ScalingMatrix[][N], int Sx, int Sy, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formScalingMatrix(ScalingMatrix, Sx, Sy);
    findTransformedMatrix(newMatrix, myVerticesMatrix, ScalingMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawAxes();
    drawPolygon(numOfVertices + 1, myArray, GREEN);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N];
    float ScalingMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    cleardevice();
    drawAxes();
    drawPolygon(numOfVertices + 1, array, WHITE);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);

    int Sx, Sy;
    cout << "Enter the value of Sx  and Sy : ";
    cin >> Sx >> Sy;
    cout << "Scaled in x => " << Sx << "\nScaled in y => " << Sy << endl;
    SCALE(myVerticesMatrix, ScalingMatrix, Sx, Sy, numOfVertices);
    drawPolygon(numOfVertices + 1, array, WHITE);
    getch();
    closegraph();

    return 0;
}
