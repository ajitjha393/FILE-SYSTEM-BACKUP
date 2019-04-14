#include <iostream.h>
#include <dos.h>
#include <graphics.h>
#include <conio.h>
void main()
{
	int gd = DETECT, gm, n, d;
	int x1, y1, x2, y2, vv = 0;
	char ch;
	cout << "\nenter the number of bubbles ";
	cin >> n;
	initgraph(&gd, &gm, "C://TC//BGI");
	cleardevice();
	int xx = getmaxx() - 5;
	rectangle(10, 10, xx, 150);
	setfillstyle(2, 9);
	floodfill(12, 12, WHITE);
	d = (xx - 10) / (n + 1);
	int yy;
	xx = 10 + d;
	//gotoxy(200,200);
	//cout<<d<<" ";
	for (int i = 0; i < n; i++)
	{

		line(xx, 150, xx, 200);
		circle(xx, 200 + 15, 15);
		xx += d;
	}
	int *col, sum;
	col = new int[n];
	for (i = 0; i < n; i++)
	{
		col[i] = i + 1;
	}
	i = 1;
	while (1)
	{
		xx = 10 + d;
		for (i = 0; i < n; i++)
		{
			setfillstyle(1, col[i]);
			floodfill(xx, 215, WHITE);
			xx = xx + d;
		}
		if (vv == 0)
		{
			getch();
			vv++;
		}
		delay(400);
		sum = 0;
		for (i = 0; i < n; i++)
		{
			sum += col[i];
		}
		int ss;
		col[0] = sum;
		for (i = 1; i < n; i++)
		{
			ss = sum;
			for (int j = 1; j < n; j++)
			{
				ss = ss - col[j];
			}
			col[i] = ss;
		}
		for (int j = 1; j < n; j++)
		{
			col[0] = col[0] - col[j];
		}
		if (kbhit())
		{
			ch = getch();
			if (ch == 27)
				//getch();
				closegraph();
			return;
		}
	}
	getch();
	closegraph();
	return;
}