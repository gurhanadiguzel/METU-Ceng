#include "the4.h"

int dp_sln(char **&arr1, char **&arr2, int nrow, int ncol1, int ncol2, int **&mem)
{ // dynamic programming
    int minCost = 0;
    mem[0][0] = 0;

    for (int column1 = 0; column1 < ncol1; column1++)
    {
        for (int column2 = 0; column2 < ncol2; column2++)
        {
            int costIns = 0;
            int costDel = 0;

            for (int row = 0; row < nrow; row++)
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
            if (!costIns && column1 == 0)
                mem[0][column2 + 1] = mem[0][column2];
            if (!costDel && column2 == 0)
                mem[column1 + 1][0] = mem[column1][0];
        }
    }
    for (int i = 1; i <= ncol1; i++)
    {
        for (int j = 1; j <= ncol2; j++)
        {
            int ins = 0, del = 0, rep = 0;
            bool flag = false;

            for (int k = 0; k < nrow; k++)
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

            for (int k = 0; k < nrow; k++)
            {
                temp1[k] = arr1[k][i - 1];
                temp2[k] = arr2[k][j - 1];
            }

            for (int k = 0; k < nrow; k++)
            {
                if (temp1[k] == temp2[k])
                {
                    temp1[k] = '+';
                    temp2[k] = '+';
                }
                for (int t = 0; t < nrow; t++)
                {
                    if ((k != t) && (temp1[k] == temp2[t]) && (temp1[k] != '+') && (temp2[t] != '+'))
                    {
                        temp1[k] = '+';
                        temp2[t] = '+';
                        rep++;
                    }
                }
            }

            for (int k = 0; k < nrow; k++)
            {
                if (temp1[k] != '+')
                {
                    flag = true;
                    rep = 0;
                }
            }

            if (flag)
            {
                for (int k = 0; k < nrow; k++)
                {
                    if ((arr1[k][i - 1] != arr2[k][j - 1]) && ('A' <= arr1[k][i - 1] && arr1[k][i - 1] <= 'Z') && ('A' <= arr2[k][j - 1] && arr2[k][j - 1] <= 'Z'))
                        rep++;

                    else if ((arr1[k][i - 1] != arr2[k][j - 1] && (((arr1[k][i - 1] == '-') && ('A' <= arr2[k][j - 1] && arr2[k][j - 1] <= 'Z')) || ((arr2[k][j - 1] == '-') && ('A' <= arr1[k][i - 1] && arr1[k][i - 1] <= 'Z')))))
                        rep += 2;
                }
            }
            rep += mem[i - 1][j - 1];

            mem[i][j] = std::min(ins, del);
            mem[i][j] = std::min(rep, mem[i][j]);
        }
    }

    minCost = mem[ncol1][ncol2];
    return minCost;
}
