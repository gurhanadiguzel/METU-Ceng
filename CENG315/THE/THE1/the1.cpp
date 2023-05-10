#include <climits>
#include <iostream>
#include <stdio.h>

void insertionSort(int *arr, long &comparison, long &swap, int size)
{
    int i = 1;
    while (i < size)
    {
        int x = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > x)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            swap++;
            comparison++;
        }
        arr[j + 1] = x;
        i++;
        if (j >= 0)
            comparison++;
    }
}

void heapify(int **arr, int size, int i, long &comparison, long &swap)
{
    int min = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = 9999;

    if (l < size && *arr[l] < *arr[min])
    {
        min = l;
        if (*arr[l] != max)
            comparison++;
    }
    else if (l < size && *arr[l] != max)
    {
        comparison++;
    }

    if (r < size && *arr[r] < *arr[min])
    {
        min = r;
        if (*arr[r] != max)
            comparison++;
    }
    else if (r < size && *arr[r] != max)
    {
        comparison++;
    }

    if (min != i)
    {
        int *tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
        swap++;
        heapify(arr, size, min, comparison, swap);
    }
}
void buildHeap(int **arr, int size, long &comparison, long &swap)
{
    int startIdx = (size / 2) - 1;

    for (int i = startIdx; i >= 0; i--)
    {
        heapify(arr, size, i, comparison, swap);
    }
}

int kWayMergeSortWithHeap(int *arr, int K, int size, long &comparison, long &swap)
{

    int number_of_calls = 1;

    if (size < K)
    {
        insertionSort(arr, comparison, swap, size);
    }
    else
    {
        int newSize = size / K;
        for (int i = 0; i < K; i++)
        {
            int **arr1 = new int *[newSize];
            for (int j = 0; j < newSize; j++)
            {
                arr1[j] = &arr[i * newSize + j];
            }
            number_of_calls += kWayMergeSortWithHeap(*arr1, K, newSize, comparison, swap);
        }

        int *heap[K];
        int use[K][2];
        int *use1[K];
        int max = max;

        for (int i = 0; i < K; i++)
        {
            heap[i] = &arr[i * size / K];
            use[i][0] = 1;
            use[i][1] = i;
            use1[i] = heap[i];
        }

        int result[size];

        for (int k = 0; k < size; k++)
        {

            if (k == 0)
                buildHeap(heap, K, comparison, swap);
            else
                heapify(heap, K, 0, comparison, swap);

            result[k] = *heap[0];
            for (int i = 0; i < K; i++)
            {
                if (use1[i] == heap[0])
                {
                    if (use[i][0] < newSize)
                    {
                        use1[i]++;
                        heap[0]++;
                        use[i][0]++;
                    }
                    else
                    {
                        use1[i] = &max;
                        heap[0] = &max;
                    }
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            arr[i] = result[i];
        }
    }

    return number_of_calls;
}

int main()
{

    // int p[10] = {20, 45, 65, 78, 98, 65, 32, 74, 9, 1};
    // int k[7] = {7, 6, 5, 4, 3, 2, 1};
    // int l[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int ex[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    long sw = 0;
    long com = 0;
    std::cout << "Number of call :" << kWayMergeSortWithHeap(ex, 4, 16, com, sw) << std::endl;
    for (int i = 0; i < 16; i++)
    {
        std::cout << ex[i] << ' ' << std::endl;
    }
    std::cout << " number of swap :" << sw << " number of comparison :" << com << std::endl;
}