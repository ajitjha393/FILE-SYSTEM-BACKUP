
/****STACK IMPLEMENTATION*****/

#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <graphics.h>
#define SIZE 10000

int myStack[SIZE];
int top = -1;

void push(int x, int y)
{
    if (top == SIZE - 2) //Since i have to add 2 points;
    {
        cout << "Stack overflow : ";
        return;
    }
    myStack[++top] = x;
    myStack[++top] = y;
}

int pop()
{
    if (top == -1)
    {
        cout << "Error : Stack Empty :(";
        return -1;
    }
    int popped = myStack[top];
    top--;
    return popped;
}
int isEmpty()
{
    if (top == -1)
        return 1;
    return 0;
}

void floodFill(int x, int y, int oldColor, int newColor)
{
    push(x, y);
    while (!isEmpty())
    {
        y = pop();
        x = pop();
        putpixel(x, y, newColor);

        if (getpixel(x + 1, y) == oldColor)
            push(x + 1, y);
        if (getpixel(x - 1, y) == oldColor)
            push(x - 1, y);
        if (getpixel(x, y + 1) == oldColor)
            push(x, y + 1);
        if (getpixel(x, y - 1) == oldColor)
            push(x, y - 1);
    }
    // if (getpixel(x, y) == oldColor)
    // {
    //     putpixel(x, y, newColor);
    //     floodFill(x + 1, y, oldColor, newColor);
    //     floodFill(x - 1, y, oldColor, newColor);
    //     floodFill(x, y + 1, oldColor, newColor);
    //     floodFill(x, y - 1, oldColor, newColor);
    // }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    rectangle(100, 100, 200, 200);
    floodFill(150, 150, 0, 3);
    getch();
    closegraph();
    return 0;
}