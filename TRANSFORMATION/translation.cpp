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

void formTranslationMatrix(float translationMatrix[][N], int tx, int ty)
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

void Translate(int myVerticesMatrix[][N], float transformationMatrix[][N], int tx, int ty, int numOfVertices)
{
    int myArray[N];
    int newMatrix[N][N];
    formTranslationMatrix(transformationMatrix, tx, ty);
    findTransformedMatrix(newMatrix, myVerticesMatrix, transformationMatrix, numOfVertices);
    createArrayFromMatrix(newMatrix, myArray, numOfVertices);
    drawAxes();
    drawPolygon(numOfVertices + 1, myArray, GREEN);
}

int main()
{

    int gd = DETECT, gm, k = 0, numOfVertices, array[N];
    int myVerticesMatrix[N][N];
    float transformationMatrix[N][N];

    initgraph(&gd, &gm, "C:\\TC\\BGI");
    cout << "Enter the number of vertices of polygon : ";
    cin >> numOfVertices;
    Input(array, numOfVertices);
    cleardevice();
    drawAxes();
    drawPolygon(numOfVertices + 1, array, WHITE);

    formCoordinateMatrix(array, myVerticesMatrix, numOfVertices);

    int tx, ty;
    cout << "Enter the value of tx  and ty : ";
    cin >> tx >> ty;
    cout << "Translated in x => " << tx << "\nTranslated in y => " << ty << endl;
    Translate(myVerticesMatrix, transformationMatrix, tx, ty, numOfVertices);
    drawPolygon(numOfVertices + 1, array, WHITE);
    getch();
    closegraph();
    // END OF TRANSLATION//

    // // ROTATION//
    // float theta;
    // cout << "ROTATION : " << endl;
    // cout << "Enter the angle of rotation : " << endl;
    // cin >> theta;
    // float thetaInRadian = theta * ((float)pi / (float)180);
    // cleardevice();
    // cout << "ROTATED BY => " << theta << endl;
    // Rotate(myVerticesMatrix, transformationMatrix, thetaInRadian, numOfVertices);
    // drawPolygon(numOfVertices + 1, array, WHITE);
    // getch();
    // //END OF ROTATION//
    // closegraph();

    return 0;
}
