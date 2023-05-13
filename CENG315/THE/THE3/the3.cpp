#include "the3.h"

using namespace std;


int recursive_sln(int size, char **&arr, int *&len, int &number_of_calls)
{ // direct recursive
    number_of_calls += 1;
    int maxLength = 0;
    if (number_of_calls == 1)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (arr[size][0] == 'I' && arr[i][1] == 'O' || arr[size][0] == 'O' && arr[i][1] == 'I' || arr[size][0] == 'S' && arr[i][1] == 'S')
            {
                maxLength = recursive_sln(i, arr, len, number_of_calls) + len[size];
                break;
            }
        }
        for (int j = 0; j < size; j++)
        {
            maxLength = max(maxLength, recursive_sln(j, arr, len, number_of_calls));
        }
    }
    else
    {
        maxLength = len[size];
        int maxLength1 = 0;
        int maxLength2 = 0;
        for (int i = size - 1; i >= 0; i--)
        {
            if (arr[size][0] == 'I' && arr[i][1] == 'O' || arr[size][0] == 'O' && arr[i][1] == 'I' || arr[size][0] == 'S' && arr[i][1] == 'S')
            {
                maxLength1 = recursive_sln(i, arr, len, number_of_calls) + len[size];
                break;
            }
        }
        for (int j = size - 1; j >= 0; j--)
        {
            if (arr[size][1] == arr[j][1])
            {
                maxLength2 = recursive_sln(j, arr, len, number_of_calls);
                break;
            }
        }
        maxLength = max(maxLength1, maxLength);
        maxLength = max(maxLength2, maxLength);
    }
    return maxLength;
}

int memoization_sln(int size, char **&arr, int *&len, int **&mem)
{ // memoization
    int maxLength = 0;
    int start, end;
    switch (arr[size][0])
    {
    case 'I':
        start = 1;
        break;
    case 'O':
        start = 0;
        break;
    case 'S':
        start = 2;
        break;
    }
    switch (arr[size][1])
    {
    case 'I':
        end = 0;
        break;
    case 'O':
        end = 1;
        break;
    case 'S':
        end = 2;
        break;
    }
    if (size == 0)
    {
        mem[0][0] = 0;
        mem[0][1] = 0;
        mem[0][2] = 0;
        mem[0][end] = len[0];
        return len[0];
    }
    else
    {
        memoization_sln(size - 1, arr, len, mem);
        for (int j = 0; j < 3; j++)
        {
            mem[size][j] = mem[size - 1][j];
        }
        mem[size][end] = max(mem[size - 1][end], mem[size - 1][start] + len[size]);
        }

    for (int k = 0; k < 3; k++)
    {
        maxLength = max(maxLength, mem[size ][k]);
    }
    return maxLength;
}



int dp_sln(int size, char **&arr, int *&len, int **&mem)
{ // dynamic programming
    for (int i = 0; i < size; i++)
    {
        int start, end;
        switch (arr[i][0])
        {
        case 'I':
            start = 1;
            break;
        case 'O':
            start = 0;
            break;
        case 'S':
            start = 2;
            break;
        }
        switch (arr[i][1])
        {
        case 'I':
            end = 0;
            break;
        case 'O':
            end = 1;
            break;
        case 'S':
            end = 2;
            break;
        }

        if (i == 0)
        {
            mem[0][0] = 0;
            mem[0][1] = 0;
            mem[0][2] = 0;
            mem[0][end] = len[0];
            continue;
        }

        for (int j = 0; j < 3; j++)
        {
            mem[i][j] = mem[i - 1][j];
        }

        mem[i][end] = max(mem[i - 1][end], mem[i - 1][start] + len[i]);
    }
    int maxLength = 0;
    for (int k = 0; k < 3; k++)
    {
        maxLength = max(maxLength, mem[size - 1][k]);
    }
    return maxLength;
}

