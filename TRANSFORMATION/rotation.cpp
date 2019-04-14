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

void findTransformedMatrix(int newMatrix[][N], int myVerticesMatrix[][N], float RotationMatrix[][N], int numOfVertices)
{
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = 0;
            for (int k = 0; k < 3; k++)
                newMatrix[i][j] += myVerticesMatrix[i][k] * RotationMatrix[k][j];
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

void formRotationalMatrix(float RotationMatrix[][N], float theta)
{
    RotationMatrix[0][0] = (float)cos(theta);
    RotationMatrix[0][1] = (float)sin(theta);
    RotationMatrix[0][2] = 0;
    RotationMatrix[1][0] = (float)(-sin(theta));
    RotationMatrix[1][1] = (float)cos(theta);
    RotationMatrix[1][2] = 0;
    RotationMatrix[2][0] = 0;
    RotationMatrix[2][1] = 0;
    RotationMatrix[2][2] = 1;
    getch();
}

void Rotate(int myVerticesMatrix[][N], float RotationMatrix[][N], float theta, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formRotationalMatrix(RotationMatrix, theta);
    findTransformedMatrix(newMatrix, myVerticesMatrix, RotationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawAxes();
    drawPolygon(numOfVertices + 1, myArray, GREEN);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N];
    float RotationMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    cleardevice();
    drawAxes();
    drawPolygon(numOfVertices + 1, array, WHITE);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);
    // ROTATION//
    float theta;
    cout << "ROTATION : " << endl;
    cout << "Enter the angle of rotation : " << endl;
    cin >> theta;
    float thetaInRadian = theta * ((float)pi / (float)180);
    cleardevice();
    cout << "ROTATED BY => " << theta << endl;
    Rotate(myVerticesMatrix, RotationMatrix, thetaInRadian, numOfVertices);
    drawPolygon(numOfVertices + 1, array, WHITE);
    getch();
    //END OF ROTATION//
    closegraph();

    return 0;
}
