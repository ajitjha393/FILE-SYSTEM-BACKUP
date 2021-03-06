#include <stdio.h>
#include <conio.h>
#include <graphics.h>

#define SAFE 1
#define NOT_SAFE 0
#define TRUE 1
#define FALSE 0

//this is the array i used to keep track of my queens
int queen[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int solution = 0;

FILE *fp;

//this function will draw the chess board using graphics
void drawSathurangam()
{
    int ctr1, ctr2;
    for (ctr1 = 0; ctr1 < 8; ctr1++)
    {
        for (ctr2 = 0; ctr2 < 8; ctr2++)
        {
            if ((ctr1 + ctr2) % 2 == 0)
                setfillstyle(SOLID_FILL, WHITE);
            else
                setfillstyle(SOLID_FILL, BLACK);
            bar(120 + (ctr2 * 50), 40 + (ctr1 * 50), 170 + (ctr2 * 50), 90 + (ctr1 * 50));
        }
    }

    rectangle(120, 40, 120 + (50 * 8), 40 + (50 * 8));
}

//each time when i update array, this function will be called
void placeQueenAndUpdate(int row, int col)
{
    queen[row] = col;
    if ((row + col) % 2 == 0)
        setcolor(BLACK);
    else
        setcolor(WHITE);
    settextstyle(4, 0, 3);
    outtextxy(135 + (col * 50), 50 + (row * 50), "Q");
}

//this will check whether the given box in the chess board is free or not
int isFree(int row, int col)
{
    if (queen[row] == col)
        return FALSE;
    else
        return TRUE;
}

//this function will tell whether the calculated row, col value exits or not
int isAvailable(int row, int col)
{
    if (row == 7 && col == 8)
    {
        closegraph();
        clrscr();
        getch();
        exit(1);
    }
    if (row > -1 && row < 8 && col > -1 && col < 8)
        return TRUE;
    else
        return FALSE;
}

//this function will check the entire left diagonal elements
int checkLeftDiagonal(int row, int col)
{
    int r, c;
    r = row - 1;
    c = col - 1;
    while (isAvailable(r, c) == TRUE)
    {
        if (isFree(r, c) == TRUE)
        {
            r--;
            c--;
        }
        else
        {
            return NOT_SAFE;
        }
    }
    return SAFE;
}

//this function will check the entire top elements in the same column
int checkTop(int row, int col)
{
    int r, c;
    r = row - 1;
    c = col;
    while (isAvailable(r, c) == TRUE)
    {
        if (isFree(r, c) == TRUE)
        {
            r--;
        }
        else
        {
            return NOT_SAFE;
        }
    }
    return SAFE;
}
//this function will check the entire right diagonal elements
int checkRightDiagonal(int row, int col)
{
    int r, c;
    r = row - 1;
    c = col + 1;
    while (isAvailable(r, c) == TRUE)
    {
        if (isFree(r, c) == TRUE)
        {
            r--;
            c++;
        }
        else
        {
            return NOT_SAFE;
        }
    }
    return SAFE;
}

//this function will tell whether the given box is free to place the queen
//or not
int isSafe(int row, int col)
{
    if (checkLeftDiagonal(row, col) == SAFE)
    {
        if (checkTop(row, col) == SAFE)
        {
            if (checkRightDiagonal(row, col) == SAFE)
            {
                return SAFE;
            }
            else
            {
                return NOT_SAFE;
            }
        }
        else
        {
            return NOT_SAFE;
        }
    }
    else
    {
        return NOT_SAFE;
    }
}

//this function will erase the queen and it will update the array
//this will happen when backtracking
void eraseQueenAndUpdate(int row, int col)
{
    if ((row + col) % 2 == 0)
        setfillstyle(SOLID_FILL, WHITE);
    else
        setfillstyle(SOLID_FILL, BLACK);
    bar(120 + (col * 50), 40 + (row * 50), (120 + (col * 50)) + 50, (40 + (row * 50)) + 50);
    setcolor(WHITE);
    rectangle(120 + (col * 50), 40 + (row * 50), (120 + (col * 50)) + 50, (40 + (row * 50)) + 50);
    queen[row] = -1;
}

//if we dont get any place for the queen, then we have to backtrack to get
//another combination
void backtrack(int *row, int *col)
{
    (*row)--;
    *col = queen[*row] + 1;
    eraseQueenAndUpdate(*row, (*col) - 1);
    if (*row == 7 && *col == 8)
    {
        backtrack(row, col);
    }
}
//this function will fill the queens
void play()
{
    int row = 0, col = 0;
    placeQueenAndUpdate(row, col);
    row++;
    while (row < 8)
    {
        while (col < 8)
        {

            if (isAvailable(row, col) == TRUE)
            {
                if (isSafe(row, col) == SAFE)
                {
                    placeQueenAndUpdate(row, col);
                    row++;
                    col = 0;
                }
                else
                    col++;
                while (col == 8)
                { //backtracking
                    backtrack(&row, &col);
                }
                if (row == 8)
                {
                    delay(100);
                    solution++;
                    fprintf(fp, "%d %d %d %d %d %d %d %d\n", queen[0], queen[1], queen[2], queen[3], queen[4], queen[5], queen[6], queen[7]);
                    if (solution == 92)
                    {
                        getch();
                        closegraph();
                        fclose(fp);
                        exit(1);
                    }
                }
            }
            else
            {
                backtrack(&row, &col);
            }
        }
    }
}
//this is the main function ;)
void main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
    drawSathurangam();
    play();
}