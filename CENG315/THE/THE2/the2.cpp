#include "the2.h"
#include <cmath>
// You may write your own helper functions here
int *countingSort(int *arr, int n, int k, long &numberOfIterations, int *helper_array, bool ascending)
{
    int *sorted = new int[n];
    int *temp = new int[k + 1];

    for (int i = 0; i < k + 1; i++)
    {
        temp[i] = 0;
    }
    for (int j = 0; j < n; j++)
    {
        temp[helper_array[j]]++;
        numberOfIterations++;
    }
    for (int i = 1; i <= k; i++)
    {
        temp[i] += temp[i - 1];
        numberOfIterations++;
    }
    if (ascending)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            sorted[temp[helper_array[j]] - 1] = arr[j];
            temp[helper_array[j]]--;
            numberOfIterations++;
        }
    }
    else
    {
        for (int j = 0; j < n; j++)
        {
            sorted[temp[helper_array[j]] - 1] = arr[j];
            temp[helper_array[j]]--;
            numberOfIterations++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (ascending)
            arr[i] = sorted[i];
        else
            arr[i] = sorted[n - i - 1];
        numberOfIterations++;
    }

    return sorted;
}

long multiDigitRadixSort(int *arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)
{
    long numberOfIterations = 0;

    for (int i = 0; maxDigitLength > 0; i++)
    {
        int *temp = new int[arraySize];
        for (int j = 0; j < arraySize; j++)
        {
            int x = pow(10, groupSize * (i + 1));
            int y = pow(10, groupSize * i);

            temp[j] = (arr[j] % x) / y;
        }
        if (maxDigitLength < groupSize)
            groupSize = maxDigitLength;

        int k = pow(10, groupSize) - 1;

        countingSort(arr, arraySize, k, numberOfIterations, temp, ascending);
        maxDigitLength -= groupSize;
    }
    return numberOfIterations;
}

int main()
{
    int arr[5] = {901, 119, 459, 888, 765};
    int *arr1 = new int[5];
    long x = 0;
    long result = multiDigitRadixSort(arr, 1, 5, 1, 3);

    for (int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << std::endl;
    }

    std::cout << result << std::endl;
}
