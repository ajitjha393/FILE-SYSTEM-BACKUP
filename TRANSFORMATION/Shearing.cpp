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

void findTransformedMatrix(int newMatrix[][N], int myVerticesMatrix[][N], float transformationMatrix[][N], int numOfVertices)
{
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newMatrix[i][j] = 0;
            for (int k = 0; k < 3; k++)
                newMatrix[i][j] += myVerticesMatrix[i][k] * transformationMatrix[k][j];
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

void formShearingMatrix(float ShearingMatrix[][N], char choice, int Shx, int Shy)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                ShearingMatrix[i][j] = 1;
            else
                ShearingMatrix[i][j] = 0;
        }

    if (choice == 'Y')
        ShearingMatrix[0][1] = Shy;
    else if (choice == 'X')
        ShearingMatrix[1][0] = Shx;
    else
    {
        ShearingMatrix[0][1] = Shx;
        ShearingMatrix[1][0] = Shy;
    }
}

void Shearing(int myVerticesMatrix[][N], float transformationMatrix[][N], char choice, int Shx, int Shy, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formShearingMatrix(transformationMatrix, choice, Shx, Shy);
    findTransformedMatrix(newMatrix, myVerticesMatrix, transformationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawAxes();
    drawPolygon(numOfVertices + 1, myArray, GREEN);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N];
    float ShearingMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    cleardevice();
    drawAxes();
    drawPolygon(numOfVertices + 1, array, WHITE);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);

    char choice;
    int Shx, Shy;
    cout << "Shearing about X OR Y axes OR BOTH ? : ";
    cin >> choice;
    if (choice == 'X')
    {
        cout << "Enter Shearing Factor Along X-axis : ";
        cin >> Shx;
        cout << "Shearing about X axis => " << endl;
    }
    else if (choice == 'Y')
    {
        cout << "Enter Shearing Factor Along Y-axis : ";
        cin >> Shy;
        cout << "Shearing about Y axis => " << endl;
    }
    else
    {
        cout << "Enter Shearing Factor Along X and Y axes : ";
        cin >> Shx >> Shy;
        cout << "Shearing about X and Y axes  =>  " << endl;
    }
    Shearing(myVerticesMatrix, ShearingMatrix, choice, Shx, Shy, numOfVertices);
    drawPolygon(numOfVertices + 1, array, WHITE);
    getch();
    closegraph();

    return 0;
}
