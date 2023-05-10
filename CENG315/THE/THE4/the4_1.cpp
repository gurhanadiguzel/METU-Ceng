#include <stdio.h>
#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>

int dp_sln(char **&arr1, char **&arr2, int nrow, int ncol1, int ncol2, int **&mem)
{ // dynamic programming
	int minCost = 0;
	int column1 = 0, column2 = 0, row = 0;
	mem[0][0] = 0;

	for (column1 = 0; column1 < ncol1; column1++)
	{
		for (column2 = 0; column2 < ncol2; column2++)
		{
			int costIns = 0;
			int costDel = 0;
			for (row = 0; row < nrow; row++)
			{
				if (column1 == 0 && arr2[row][column2] != '-')
				{
					costIns++;
					mem[0][column2 + 1] = costIns + mem[0][column2];
				}
				if (column2 == 0 && arr1[row][column1] != '-')
				{
					costDel++;
					mem[column1 + 1][0] = costDel + mem[column1][0];
				}
			}
		}
	}
	for (int i = 1; i <= ncol1; i++)
	{
		for (int j = 1; j <= ncol2; j++)
		{
			int ins = 0, del = 0, rep = 0;
			for (int k = 0; k < row; k++)
			{
				if (arr2[k][j - 1] != '-')
					ins++;
				if (arr1[k][i - 1] != '-')
					del++;
			}
			ins += mem[i][j - 1];
			del += mem[i - 1][j];

			char *temp1 = new char[nrow];
			char *temp2 = new char[nrow];

			for (int l = 0; l < nrow; l++)
			{
				temp1[l] = arr1[l][i - 1];
				temp2[l] = arr2[l][j - 1];
				if (temp1[l] == temp2[l])
				{
					temp1[l] = '+';
					temp2[l] = '+';
				}
			}
			if (i == 1 && j == 3)
			{
				std::cout << temp1[0] << temp1[1] << temp1[2] << temp1[3] << std::endl;
				std::cout << temp2[0] << temp2[1] << temp2[2] << temp2[3] << std::endl;
			}

			for (int l = 0; l < nrow; l++)
			{
				for (int t = 0; t < nrow; t++)
				{
					if ((l != t) && (temp1[l] == temp2[t]) && (temp1[l] != '+') && (temp2[t] != '+'))
					{
						temp1[l] = '+';
						temp2[t] = '+';
						rep++;
					}
				}
			}
			for (int l = 0; l < nrow; l++)
			{
				for (int t = 0; t < nrow; t++)
				{
					if ((temp1[l] != temp2[t]) && ('A' <= temp1[l] && temp1[l] <= 'Z') && ('A' <= temp2[t] && temp2[t] <= 'Z') && (temp1[l] != '+') && (temp2[t] != '+'))
					{
						temp1[l] = '+';
						temp2[t] = '+';
						rep++;
					}
					if ((temp1[l] != temp2[t] && (temp1[l] != '+') && (temp2[t] != '+') && (((temp1[l] == '-') && ('A' <= temp2[t] && temp2[t] <= 'Z')) || ((temp2[t] == '-') && ('A' <= temp1[l] && temp1[l] <= 'Z')))))
					{
						temp1[l] = '+';
						temp2[t] = '+';
						rep += 2;
					}
				}
			}
			std::cout << "Rep:" << rep;
			rep += mem[i - 1][j - 1];
			std::cout << " i: " << i << " j: " << j << std::endl;
			std::cout << "Rep:" << rep;
			std::cout << " INS:" << ins;
			std::cout << " DEL:" << del << std::endl;
			mem[i][j] = std::min(ins, del);
			mem[i][j] = std::min(rep, mem[i][j]);
		}
	}

	minCost = mem[ncol1][ncol2];
	return minCost;
}

int main()
{

	char **box1, **box2;
	int nrow = 4;
	int ncol1 = 4;
	int ncol2 = 4;

	box1 = new char *[nrow];
	box2 = new char *[nrow];

	for (int i = 0; i < nrow; i++)
	{
		box1[i] = new char[ncol1];
		box2[i] = new char[ncol2];
	}

	int **mem = new int *[ncol1 + 1];
	for (int i = 0; i <= ncol1; i++)
	{
		mem[i] = new int[ncol2 + 1];
		for (int j = 0; j <= ncol2; j++)
			mem[i][j] = -1;
	}

	box1[0][0] = '-';
	box1[0][1] = 'M';
	box1[0][2] = 'V';
	box1[0][3] = 'R';
	box1[1][0] = 'M';
	box1[1][1] = '-';
	box1[1][2] = 'R';
	box1[1][3] = '-';
	box1[2][0] = 'R';
	box1[2][1] = 'M';
	box1[2][2] = 'M';
	box1[2][3] = '-';
	box1[3][0] = 'V';
	box1[3][1] = 'M';
	box1[3][2] = '-';
	box1[3][3] = 'R';

	box2[0][0] = 'M';
	box2[0][1] = '-';
	box2[0][2] = '-';
	box2[0][3] = 'V';
	box2[1][0] = 'V';
	box2[1][1] = 'R';
	box2[1][2] = 'R';
	box2[1][3] = 'M';
	box2[2][0] = '-';
	box2[2][1] = '-';
	box2[2][2] = '-';
	box2[2][3] = '-';
	box2[3][0] = '-';
	box2[3][1] = 'M';
	box2[3][2] = '-';
	box2[3][3] = 'R';

	// "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
	// EXAMPLE (b)
	/*
	box1[0][0] = '-'; box1[0][1] = 'B'; box1[0][2] = 'C';
	box1[1][0] = 'B'; box1[1][1] = '-'; box1[1][2] = 'C';

	box2[0][0] = 'A'; box2[0][1] = '-'; box2[0][2] = 'C'; box2[0][3] = 'A'; box2[0][4] = 'B';
	box2[1][0] = '-'; box2[1][1] = 'C'; box2[1][2] = 'C'; box2[1][3] = 'A'; box2[1][4] = '-';
	*/

	// EXAMPLE (c)
	/*
	box1[0][0] = 'A'; box1[0][1] = 'A'; box1[0][2] = 'C'; box1[0][3] = 'B'; box1[0][4] = '-';
	box1[1][0] = 'B'; box1[1][1] = 'C'; box1[1][2] = '-'; box1[1][3] = '-'; box1[1][4] = 'A';
	box1[2][0] = 'A'; box1[2][1] = 'C'; box1[2][2] = '-'; box1[2][3] = 'A'; box1[2][4] = '-';
	box1[3][0] = '-'; box1[3][1] = 'C'; box1[3][2] = '-'; box1[3][3] = '-'; box1[3][4] = 'C';

	box2[0][0] = 'A'; box2[0][1] = 'C'; box2[0][2] = 'B'; box2[0][3] = '-'; box2[0][4] = 'A'; box2[0][5] = 'B'; box2[0][6] = 'A';
	box2[1][0] = 'B'; box2[1][1] = 'A'; box2[1][2] = 'B'; box2[1][3] = '-'; box2[1][4] = 'C'; box2[1][5] = '-'; box2[1][6] = 'C';
	box2[2][0] = 'B'; box2[2][1] = '-'; box2[2][2] = '-'; box2[2][3] = 'A'; box2[2][4] = 'C'; box2[2][5] = 'A'; box2[2][6] = 'B';
	box2[3][0] = 'C'; box2[3][1] = '-'; box2[3][2] = 'B'; box2[3][3] = '-'; box2[3][4] = 'B'; box2[3][5] = 'A'; box2[3][6] = 'B';
	*/

	// EXAMPLE (d)
	/*
	box1[0][0] = '-'; box1[0][1] = 'Y'; box1[0][2] = 'W'; box1[0][3] = 'Y'; box1[0][4] = '-'; box1[0][5] = '-';
	box1[1][0] = '-'; box1[1][1] = 'Z'; box1[1][2] = 'Y'; box1[1][3] = 'Y'; box1[1][4] = '-'; box1[1][5] = 'W';
	box1[2][0] = 'W'; box1[2][1] = 'Y'; box1[2][2] = 'Z'; box1[2][3] = 'Y'; box1[2][4] = '-'; box1[2][5] = '-';
	box1[3][0] = 'W'; box1[3][1] = 'W'; box1[3][2] = '-'; box1[3][3] = 'Y'; box1[3][4] = '-'; box1[3][5] = 'Y';
	box1[4][0] = '-'; box1[4][1] = 'Z'; box1[4][2] = '-'; box1[4][3] = '-'; box1[4][4] = 'Z'; box1[4][5] = 'Z';

	box2[0][0] = 'Z'; box2[0][1] = 'W'; box2[0][2] = '-';
	box2[1][0] = 'W'; box2[1][1] = 'Y'; box2[1][2] = '-';
	box2[2][0] = 'Y'; box2[2][1] = 'Z'; box2[2][2] = 'Y';
	box2[3][0] = '-'; box2[3][1] = 'Z'; box2[3][2] = '-';
	box2[4][0] = '-'; box2[4][1] = '-'; box2[4][2] = '-';
	*/

	// EXAMPLE (e)
	/*
	box1[0][0] = 'A'; box1[0][1] = 'B'; box1[0][2] = 'C'; box1[0][3] = 'A'; box1[0][4] = 'B'; box1[0][5] = 'C';
	box1[1][0] = 'B'; box1[1][1] = 'C'; box1[1][2] = 'C'; box1[1][3] = 'A'; box1[1][4] = '-'; box1[1][5] = 'A';

	box2[0][0] = 'A'; box2[0][1] = 'B'; box2[0][2] = 'B'; box2[0][3] = 'A';
	box2[1][0] = 'B'; box2[1][1] = 'A'; box2[1][2] = '-'; box2[1][3] = 'C';
	*/

	// "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"
	// EXAMPLE (f)
	/*
	box1[0][0] = '-'; box1[0][1] = 'M'; box1[0][2] = 'V'; box1[0][3] = 'R';
	box1[1][0] = 'M'; box1[1][1] = '-'; box1[1][2] = 'R'; box1[1][3] = '-';
	box1[2][0] = 'R'; box1[2][1] = 'M'; box1[2][2] = 'M'; box1[2][3] = '-';
	box1[3][0] = 'V'; box1[3][1] = 'M'; box1[3][2] = '-'; box1[3][3] = 'R';

	box2[0][0] = 'M'; box2[0][1] = '-'; box2[0][2] = '-'; box2[0][3] = 'V';
	box2[1][0] = 'V'; box2[1][1] = 'R'; box2[1][2] = 'R'; box2[1][3] = 'M';
	box2[2][0] = '-'; box2[2][1] = '-'; box2[2][2] = '-'; box2[2][3] = '-';
	box2[3][0] = '-'; box2[3][1] = 'M'; box2[3][2] = '-'; box2[3][3] = 'R';
	*/

	dp_sln(box1, box2, nrow, ncol1, ncol2, mem);

	for (int i = 0; i <= ncol1; i++)
	{
		for (int j = 0; j <= ncol2; j++)
		{
			std::cout << mem[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}