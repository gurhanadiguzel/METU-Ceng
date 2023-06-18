#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hw2_output.h"

struct Matrix {
    int row;
    int column;
    int** matrix;
};

sem_t* rowSemaphores;
sem_t** columnSemaphores;
sem_t* mutex;
int* columnList;

struct Matrix matrix1, matrix2, matrix3, matrix4;
struct Matrix sumMatrix1, sumMatrix2, multMatrix;

void printMatrix(struct Matrix matrix) {
    // printf("\n");
    for (int row = 0; row < matrix.row; row++) {
        for (int column = 0; column < matrix.column; column++) {
            printf("%d", matrix.matrix[row][column]);
            if (column != (matrix.column - 1))
                printf(" ");
        }
        if (row != (matrix.row - 1))
            printf("\n");
    }
}

void readInputs() {
    scanf("%d", &matrix1.row);
    scanf("%d", &matrix1.column);
    matrix1.matrix = (int**)malloc(sizeof(int*) * matrix1.row);
    for (int row = 0; row < matrix1.row; row++) {
        matrix1.matrix[row] = (int*)malloc(sizeof(int) * matrix1.column);
    }
    for (int row = 0; row < matrix1.row; row++) {
        for (int column = 0; column < matrix1.column; column++) {
            scanf("%d", &matrix1.matrix[row][column]);
        }
    }
    //printMatrix(matrix1);

    scanf("%d", &matrix2.row);
    scanf("%d", &matrix2.column);
    matrix2.matrix = (int**)malloc(sizeof(int*) * matrix2.row);
    for (int row = 0; row < matrix2.row; row++) {
        matrix2.matrix[row] = (int*)malloc(sizeof(int) * matrix2.column);
    }
    for (int row = 0; row < matrix2.row; row++) {
        for (int column = 0; column < matrix2.column; column++) {
            scanf("%d", &matrix2.matrix[row][column]);
        }
    }
    //printMatrix(matrix2);

    scanf("%d", &matrix3.row);
    scanf("%d", &matrix3.column);
    matrix3.matrix = (int**)malloc(sizeof(int*) * matrix3.row);
    for (int row = 0; row < matrix3.row; row++) {
        matrix3.matrix[row] = (int*)malloc(sizeof(int) * matrix3.column);
    }
    for (int row = 0; row < matrix3.row; row++) {
        for (int column = 0; column < matrix3.column; column++) {
            scanf("%d", &matrix3.matrix[row][column]);
        }
    }
    //printMatrix(matrix3);

    scanf("%d", &matrix4.row);
    scanf("%d", &matrix4.column);
    matrix4.matrix = (int**)malloc(sizeof(int*) * matrix4.row);
    for (int row = 0; row < matrix4.row; row++) {
        matrix4.matrix[row] = (int*)malloc(sizeof(int) * matrix4.column);
    }
    for (int row = 0; row < matrix4.row; row++) {
        for (int column = 0; column < matrix4.column; column++) {
            scanf("%d", &matrix4.matrix[row][column]);
        }
    }
    //printMatrix(matrix4);
}

void* firstMatrixSum(void* arg) {
    int row = (long)arg;
    for (int column = 0; column < sumMatrix1.column; column++) {
        sumMatrix1.matrix[row][column] = matrix1.matrix[row][column] + matrix2.matrix[row][column];
        hw2_write_output(0, row, column, sumMatrix1.matrix[row][column]);

        // if (row == sumMatrix1.row - 1 && column == sumMatrix1.column - 1)
        //     printf("FIRST MATRIX SUM HAS BEEN FINISHED\n");
    }
    sem_post(&(rowSemaphores[row]));  //  Wait for the finish row and do signal.
}

void* secondMatrixSum(void* arg) {
    int row = (long)arg;
    for (int column = 0; column < sumMatrix2.column; column++) {
        sumMatrix2.matrix[row][column] = matrix3.matrix[row][column] + matrix4.matrix[row][column];
        hw2_write_output(1, row, column, sumMatrix2.matrix[row][column]);

        sem_wait(&(mutex[column]));
        columnList[column]++;
        if (columnList[column] == sumMatrix2.row) {
            for (int row = 0; row < sumMatrix1.row; row++) {
                sem_post(&(columnSemaphores[row][column]));
            }
        }
        sem_post(&(mutex[column]));

        // if (row == sumMatrix2.row - 1 && column == sumMatrix2.column - 1)
        //  printf("SECOND MATRIX SUM HAS BEEN FINISHED\n");
    }
}

void* matrixMultiplication(void* args) {
    int row = (long)args;
    int result;
    sem_wait((&rowSemaphores[row]));

    for (int column2 = 0; column2 < sumMatrix2.column; column2++) {
        result = 0;
        sem_wait(&(columnSemaphores[row][column2]));
        for (int column1 = 0; column1 < sumMatrix1.column; column1++) {
            result += sumMatrix1.matrix[row][column1] * sumMatrix2.matrix[column1][column2];
            // printf("%d %d and %d %d\n", row, column1, column1, column2);
        }
        multMatrix.matrix[row][column2] = result;

        hw2_write_output(2, row, column2, result);
    }
}

void initSemaphores(int row, int column) {
    for (int i = 0; i < row; i++) {
        sem_init(&(rowSemaphores[i]), 0600, 0);
    }

    for (int j = 0; j < row; j++) {
        for (int i = 0; i < column; i++) {
            sem_init(&(columnSemaphores[j][i]), 0600, 0);
        }
    }

    for (int i = 0; i < column; i++) {
        sem_init(&(mutex[i]), 0600, 1);
    }
}

void closeSemaphores(int row, int column) {
    for (int i = 0; i < row; i++) {
        sem_close(&(rowSemaphores[i]));
    }

    for (int j = 0; j < row; j++) {
        for (int i = 0; i < column; i++) {
            sem_close(&(columnSemaphores[j][i]));
        }
    }

    for (int i = 0; i < column; i++) {
        sem_close(&(mutex[i]));
    }
}

int main() {
    hw2_init_output();

    readInputs();
    // printf("Input have been readed\n");

    sumMatrix1.row = matrix1.row;
    sumMatrix1.column = matrix1.column;
    sumMatrix1.matrix = (int**)malloc(sizeof(int*) * sumMatrix1.row);
    for (int row = 0; row < sumMatrix1.row; row++) {
        sumMatrix1.matrix[row] = (int*)malloc(sizeof(int) * sumMatrix1.column);
    }

    sumMatrix2.row = matrix3.row;
    sumMatrix2.column = matrix3.column;
    sumMatrix2.matrix = (int**)malloc(sizeof(int*) * sumMatrix2.row);
    for (int row = 0; row < sumMatrix2.row; row++) {
        sumMatrix2.matrix[row] = (int*)malloc(sizeof(int) * sumMatrix2.column);
    }

    multMatrix.row = matrix1.row;
    multMatrix.column = matrix3.column;
    multMatrix.matrix = (int**)malloc(sizeof(int*) * multMatrix.row);
    for (int row = 0; row < multMatrix.row; row++) {
        multMatrix.matrix[row] = (int*)malloc(sizeof(int) * multMatrix.column);
    }

    mutex = (sem_t*)malloc(multMatrix.column * sizeof(sem_t));
    rowSemaphores = (sem_t*)malloc(multMatrix.row * sizeof(sem_t));

    columnSemaphores = (sem_t**)malloc(multMatrix.row * sizeof(sem_t*));
    for (int row = 0; row < multMatrix.row; row++) {
        columnSemaphores[row] = (sem_t*)malloc(multMatrix.column * sizeof(sem_t));
    }

    columnList = (int*)malloc(sumMatrix2.column * sizeof(int));
    for (int i = 0; i < sumMatrix2.column; i++) {
        columnList[i] = 0;
    }

    pthread_t* firstSumThreads = (pthread_t*)malloc(sumMatrix1.row * sizeof(pthread_t));
    pthread_t* secondSumThreads = (pthread_t*)malloc(sumMatrix2.row * sizeof(pthread_t));
    pthread_t* multiplicationThreads = (pthread_t*)malloc(multMatrix.row * sizeof(pthread_t));

    initSemaphores(multMatrix.row, multMatrix.column);

    for (int row = 0; row < sumMatrix1.row; row++) {
        pthread_create(&(firstSumThreads[row]), NULL, firstMatrixSum, (void*)row);
    }

    for (int row = 0; row < sumMatrix2.row; row++) {
        pthread_create(&(secondSumThreads[row]), NULL, secondMatrixSum, (void*)row);
    }

    for (int row = 0; row < multMatrix.row; row++) {
        pthread_create(&(multiplicationThreads[row]), NULL, matrixMultiplication, (void*)row);
    }

    for (int row = 0; row < sumMatrix1.row; row++) {
        pthread_join(firstSumThreads[row], NULL);
    }

    for (int row = 0; row < sumMatrix2.row; row++) {
        pthread_join(secondSumThreads[row], NULL);
    }

    for (int row = 0; row < multMatrix.row; row++) {
        pthread_join(multiplicationThreads[row], NULL);
    }
    // printMatrix(sumMatrix1);
    // printMatrix(sumMatrix2);
    printMatrix(multMatrix);
    closeSemaphores(multMatrix.row, multMatrix.column);
    return 0;
}