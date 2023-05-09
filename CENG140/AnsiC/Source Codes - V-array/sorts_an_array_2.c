    /*
     * C program to accept N numbers and arrange them in an ascending order
     */
    #include <stdio.h>
     
    int main()
    {
        int i, j, temp, n=10;
        int number[10]={112,23,45,41,47,84,1,47,12,10};
           
        for (i = 0; i < n; ++i)
        {
            for (j = i + 1; j < n; ++j)
            {
                if (number[i] > number[j])
                {
                    temp =  number[i];
                    number[i] = number[j];
                    number[j] = temp;
                }
            }
        }

        printf("The numbers arranged in ascending order are given below \n");
        for (i = 0; i < n; ++i)
        printf("%d\n", number[i]);
        system("pause");
        return 0;
    }
