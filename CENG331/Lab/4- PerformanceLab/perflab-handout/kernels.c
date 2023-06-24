/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#define R(t1, t2, t3, t4) (t1->red + t2->red + t3->red + t4->red) / 4
#define G(t1, t2, t3, t4) (t1->green + t2->green + t3->green + t4->green) / 4
#define B(t1, t2, t3, t4) (t1->blue + t2->blue + t3->blue + t4->blue) / 4
#define R2(temp1, temp2) (temp1->red * temp2->red)
#define G2(temp1, temp2) (temp1->green * temp2->green)
#define B2(temp1, temp2) (temp1->blue * temp2->blue)
#define RGB(temp1, temp2) (R2(temp1, temp2) + G2(temp1, temp2) + B2(temp1, temp2))

/*
 * Please fill in the following team_t struct
 */
team_t team = {
    "Baby Monkeys", /* Team Name */

    "e2448025", /* First student ID */
    "Gürhan İlhan Adıgüzel",   /* First student name */

    "e2448090", /* Second student ID */
    "Aybüke Aksoy",    /* Second student name */

    "", /* Third student ID */
    ""  /* Third student Name */
};

/********************
 * CONVOLUTION KERNEL
 ********************/

/***************************************************************
 * Your different versions of the convolution functions  go here
 ***************************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, k, l;
    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            dst[RIDX(i, j, dim)] = 0;
            for (k = 0; k < 8; k++)
                for (l = 0; l < 8; l++)
                {
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].red *
                                            ker[RIDX(k, l, 8)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].green *
                                            ker[RIDX(k, l, 8)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].blue *
                                            ker[RIDX(k, l, 8)].blue;
                }
        }
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */

char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, res, initIndex = dim - 7;
    pixel kernValues[64];
    pixel *tmpSrc, *rwSrc;
    unsigned *rwDst;

    for (i = 0; i < 64; i++)
        kernValues[i] = ker[i];

    for (i = initIndex; i > 0; --i)
    {
        tmpSrc = src;
        rwDst = dst;
        for (j = initIndex; j > 0; --j)
        {
            rwSrc = tmpSrc;
            res = RGB(rwSrc, kernValues);
            res += RGB((rwSrc + 1), (kernValues + 1));
            res += RGB((rwSrc + 2), (kernValues + 2));
            res += RGB((rwSrc + 3), (kernValues + 3));
            res += RGB((rwSrc + 4), (kernValues + 4));
            res += RGB((rwSrc + 5), (kernValues + 5));
            res += RGB((rwSrc + 6), (kernValues + 6));
            res += RGB((rwSrc + 7), (kernValues + 7));
            rwSrc += dim;
            res += RGB(rwSrc, (kernValues + 8));
            res += RGB((rwSrc + 1), (kernValues + 9));
            res += RGB((rwSrc + 2), (kernValues + 10));
            res += RGB((rwSrc + 3), (kernValues + 11));
            res += RGB((rwSrc + 4), (kernValues + 12));
            res += RGB((rwSrc + 5), (kernValues + 13));
            res += RGB((rwSrc + 6), (kernValues + 14));
            res += RGB((rwSrc + 7), (kernValues + 15));
            rwSrc += dim;
            res += RGB(rwSrc, (kernValues + 16));
            res += RGB((rwSrc + 1), (kernValues + 17));
            res += RGB((rwSrc + 2), (kernValues + 18));
            res += RGB((rwSrc + 3), (kernValues + 19));
            res += RGB((rwSrc + 4), (kernValues + 20));
            res += RGB((rwSrc + 5), (kernValues + 21));
            res += RGB((rwSrc + 6), (kernValues + 22));
            res += RGB((rwSrc + 7), (kernValues + 23));
            rwSrc += dim;
            res += RGB(rwSrc, (kernValues + 24));
            res += RGB((rwSrc + 1), (kernValues + 25));
            res += RGB((rwSrc + 2), (kernValues + 26));
            res += RGB((rwSrc + 3), (kernValues + 27));
            res += RGB((rwSrc + 4), (kernValues + 28));
            res += RGB((rwSrc + 5), (kernValues + 29));
            res += RGB((rwSrc + 6), (kernValues + 30));
            res += RGB((rwSrc + 7), (kernValues + 31));
            rwSrc += dim;

            res += RGB(rwSrc, (kernValues + 32));
            res += RGB((rwSrc + 1), (kernValues + 33));
            res += RGB((rwSrc + 2), (kernValues + 34));
            res += RGB((rwSrc + 3), (kernValues + 35));
            res += RGB((rwSrc + 4), (kernValues + 36));
            res += RGB((rwSrc + 5), (kernValues + 37));
            res += RGB((rwSrc + 6), (kernValues + 38));
            res += RGB((rwSrc + 7), (kernValues + 39));
            rwSrc += dim;

            res += RGB(rwSrc, (kernValues + 40));
            res += RGB((rwSrc + 1), (kernValues + 41));
            res += RGB((rwSrc + 2), (kernValues + 42));
            res += RGB((rwSrc + 3), (kernValues + 43));
            res += RGB((rwSrc + 4), (kernValues + 44));
            res += RGB((rwSrc + 5), (kernValues + 45));
            res += RGB((rwSrc + 6), (kernValues + 46));
            res += RGB((rwSrc + 7), (kernValues + 47));
            rwSrc += dim;

            res += RGB(rwSrc, (kernValues + 48));
            res += RGB((rwSrc + 1), (kernValues + 49));
            res += RGB((rwSrc + 2), (kernValues + 50));
            res += RGB((rwSrc + 3), (kernValues + 51));
            res += RGB((rwSrc + 4), (kernValues + 52));
            res += RGB((rwSrc + 5), (kernValues + 53));
            res += RGB((rwSrc + 6), (kernValues + 54));
            res += RGB((rwSrc + 7), (kernValues + 55));
            rwSrc += dim;

            res += RGB(rwSrc, (kernValues + 56));
            res += RGB((rwSrc + 1), (kernValues + 57));
            res += RGB((rwSrc + 2), (kernValues + 58));
            res += RGB((rwSrc + 3), (kernValues + 59));
            res += RGB((rwSrc + 4), (kernValues + 60));
            res += RGB((rwSrc + 5), (kernValues + 61));
            res += RGB((rwSrc + 6), (kernValues + 62));
            res += RGB((rwSrc + 7), (kernValues + 63));
            ++tmpSrc;
            *rwDst++ = res;
        }
        src += dim;
        dst += dim;
    }
}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions()
{
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}

/************************
 * AVERAGE POOLING KERNEL
 ************************/

/*********************************************************
 * Your different versions of the average pooling  go here
 *********************************************************/

/*
 * naive_average_pooling - The naive baseline version of average pooling
 */
char naive_average_pooling_descr[] = "Naive Average Pooling: Naive baseline implementation";
void naive_average_pooling(int dim, pixel *src, pixel *dst)
{
    int i, j, k, l;

    for (i = 0; i < dim / 2; i++)
        for (j = 0; j < dim / 2; j++)
        {
            dst[RIDX(i, j, dim / 2)].red = 0;
            dst[RIDX(i, j, dim / 2)].green = 0;
            dst[RIDX(i, j, dim / 2)].blue = 0;
            for (k = 0; k < 2; k++)
            {
                for (l = 0; l < 2; l++)
                {
                    dst[RIDX(i, j, dim / 2)].red += src[RIDX(i * 2 + k, j * 2 + l, dim)].red;
                    dst[RIDX(i, j, dim / 2)].green += src[RIDX(i * 2 + k, j * 2 + l, dim)].green;
                    dst[RIDX(i, j, dim / 2)].blue += src[RIDX(i * 2 + k, j * 2 + l, dim)].blue;
                }
            }
            dst[RIDX(i, j, dim / 2)].red /= 4;
            dst[RIDX(i, j, dim / 2)].green /= 4;
            dst[RIDX(i, j, dim / 2)].blue /= 4;
        }
}

/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";
void average_pooling(int dim, pixel *src, pixel *dst)
{
    src += dim;
    src++;

    int half = dim / 2;
    for (int i = 1; i < dim; i += 2)
    {
        pixel *tempDst = dst;
        pixel *tempSrc = src;
        for (int j = 1; j < dim; j += 2)
        {
            tempDst->red = R(tempSrc, (tempSrc - 1), (tempSrc - dim), (tempSrc - dim - 1));
            tempDst->green = G(tempSrc, (tempSrc - 1), (tempSrc - dim), (tempSrc - dim - 1));
            tempDst->blue = B(tempSrc, (tempSrc - 1), (tempSrc - dim), (tempSrc - dim - 1));
            tempSrc += 2;
            tempDst++;
        }
        src += dim;
        src += dim;
        dst += half;
    }
}

/******************************************************************************
 * register_average_pooling_functions - Register all of your different versions
 *     of the average pooling  with the driver by calling the
 *     add_average_pooling_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ******************************************************************************/

void register_average_pooling_functions()
{
    add_average_pooling_function(&naive_average_pooling, naive_average_pooling_descr);
    add_average_pooling_function(&average_pooling, average_pooling_descr);
    /* ... Register additional test functions here */
}
