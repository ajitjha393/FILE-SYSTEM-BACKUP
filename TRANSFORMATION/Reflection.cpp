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

void formReflectionMatrix(float ReflectionMatrix[][N], char choice)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ReflectionMatrix[i][j] = 0;

    if (choice == 'X')
    {
        ReflectionMatrix[0][0] = 1;
        ReflectionMatrix[1][1] = -1;
        ReflectionMatrix[2][2] = 1;
    }
    else if (choice == 'Y')
    {
        ReflectionMatrix[0][0] = -1;
        ReflectionMatrix[1][1] = 1;
        ReflectionMatrix[2][2] = 1;
    }
    else
    {
        ReflectionMatrix[0][0] = -1;
        ReflectionMatrix[1][1] = -1;
        ReflectionMatrix[2][2] = 1;
    }
}

void Reflection(int myVerticesMatrix[][N], float transformationMatrix[][N], char choice, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formReflectionMatrix(transformationMatrix, choice);
    findTransformedMatrix(newMatrix, myVerticesMatrix, transformationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawAxes();
    drawPolygon(numOfVertices + 1, myArray, GREEN);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N];
    float ReflectionMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    cleardevice();
    drawAxes();
    drawPolygon(numOfVertices + 1, array, WHITE);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);

    char choice;
    cout << "Reflection about X OR Y axes OR BOTH ? : ";
    cin >> choice;
    if (choice == 'X')
        cout << "Reflection about X axis => " << endl;
    else if (choice == 'Y')
        cout << "Reflection about Y axis => " << endl;
    else
        cout << "Reflection about X and Y axes => " << endl;

    Reflection(myVerticesMatrix, ReflectionMatrix, choice, numOfVertices);
    drawPolygon(numOfVertices + 1, array, WHITE);
    getch();
    closegraph();

    return 0;
}
