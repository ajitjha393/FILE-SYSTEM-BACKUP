#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#define N 20
#define pi 3.142

void printMatrix(int myMatrix[][N], int numOfVertices)
{

    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << myMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Input(int array[], int numOfVertices)
{
    cout << "Enter the x y value of the vertices of polygon : " << endl;
    for (int i = 0; i < 2 * numOfVertices; i++)
        cin >> array[i];
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

void formTranslationMatrix(int translationMatrix[][N], int tx, int ty)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                translationMatrix[i][j] = 1;
            else
                translationMatrix[i][j] = 0;
        }
    translationMatrix[2][0] = tx;
    translationMatrix[2][1] = ty;
}

void findTransformedMatrix(int newMatrix[][N], int myVerticesMatrix[][N], int transformationMatrix[][N], int numOfVertices)
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
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
                myArray[k++] = newMatrix[i][j];
        }
    }
    myArray[k++] = myArray[0];
    myArray[k] = myArray[1];
}

void Translate(int myVerticesMatrix[][N], int transformationMatrix[][N], int tx, int ty, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formTranslationMatrix(transformationMatrix, tx, ty);
    findTransformedMatrix(newMatrix, myVerticesMatrix, transformationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawpoly(numOfVertices + 1, myArray);
}

void formRotationalMatrix(int transformationMatrix[][N], float theta)
{
    transformationMatrix[0][0] = cos(theta);
    transformationMatrix[0][1] = sin(theta);
    transformationMatrix[0][2] = 0;
    transformationMatrix[1][0] = -sin(theta);
    transformationMatrix[1][1] = cos(theta);
    transformationMatrix[1][2] = 0;
    transformationMatrix[2][0] = 0;
    transformationMatrix[2][1] = 0;
    transformationMatrix[2][2] = 1;
}

void Rotate(int myVerticesMatrix[][N], int transformationMatrix[][N], float theta, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formRotationalMatrix(transformationMatrix, theta);
    findTransformedMatrix(newMatrix, myVerticesMatrix, transformationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    for (int i = 0; i < 2 * numOfVertices + 2; i++)
        cout << myArray[i] << endl;
    getch();
    drawpoly(numOfVertices + 1, myArray);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N], transformationMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    drawpoly(numOfVertices + 1, array);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);
    //TRANSLATION//
    //formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);

    // printMatrix(myVerticesMatrix, numOfVertices);

    //getch();

    int tx, ty;
    cout << "Enter the value of tx  and ty : ";
    cin >> tx >> ty;

    Translate(myVerticesMatrix, transformationMatrix, tx, ty, numOfVertices);
    getch();
    cleardevice();
    // END OF TRANSLATION//

    // ROTATION//
    float theta;
    cout << "ROTATION : " << endl;
    cout << "Enter the angle of rotation" << endl;
    cin >> theta;
    theta *= (pi / 180);
    drawpoly(numOfVertices + 1, array);
    Rotate(myVerticesMatrix, transformationMatrix, theta, numOfVertices);
    getch();
    //END OF ROTATION//
    closegraph();

    return 0;
}
