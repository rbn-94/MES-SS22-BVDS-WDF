/**
 * @author Robin Franzen
 * @email robin.franzen94@gmail.com
 * @create date 2022-05-21 12:27:11
 * @modify date 2022-05-21 12:27:11
 * @desc DSP code for wave digital filter of 19. degree
 */

#include "wdf19deg.h"

#define NUM_DELAY_BLOCKS 9

 /* Coefficients */
double alphas[9] = {
    -0.226119,
    0.397578,
    0.160677,
    0.049153,
    -0.063978,
    -0.423068,
    0.258673,
    0.094433,
    0.015279
};

double weights[4] = {
        1.0,
        1.0,
        1.0,
        1.0
};

/* Globals for delays T and 2T */
double delay2T_1[NUM_DELAY_BLOCKS - 1][2];
double delayT_1[1];

double delay2T_2[NUM_DELAY_BLOCKS - 1][4];
double delayT_2[2];

double delay2T_3[NUM_DELAY_BLOCKS - 1][8];
double delayT_3[4];

/* Globals for HP output delays T */
// Don't know why these delay values... ask Hendrik/Patrick
double delayHP1[16 + 8];
double delayHP2[16];

/* Prototypes */
void twoPortCrossAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2);
void twoPortAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2);
double wdf19deg(double x, double* delays2T, double* delayT, int n, double* yhp);

void initArray(double* array, int size);
void init2dArray(double* array, int rows, int cols);

void initDelays()
{
    init2dArray(delay2T_1[0], NUM_DELAY_BLOCKS - 1, 2);
    init2dArray(delay2T_2[0], NUM_DELAY_BLOCKS - 1, 4);
    init2dArray(delay2T_3[0], NUM_DELAY_BLOCKS - 1, 8);

    initArray(delayT_1, 1);
    initArray(delayT_2, 2);
    initArray(delayT_3, 4);
}

double octaveFilterbank(double x)
{
    double yhp1, yhp2, yhp3;
    double ytp1, ytp2, ytp3;
    double b = 0.0;
    int i;

    ytp1 = wdf19deg(x, delay2T_1[0], delayT_1, 1, &yhp1);
    ytp2 = wdf19deg(ytp1, delay2T_2[0], delayT_2, 2, &yhp2);
    ytp3 = wdf19deg(ytp2, delay2T_3[0], delayT_3, 3, &yhp3);

    // Calculate output
    b = weights[0] * delayHP1[23] + weights[1] * delayHP2[15] + weights[2] * yhp3 + weights[3] * ytp3;

    // Shift delays
    for (i = 23; i > 0; i--)
    {
        delayHP1[i] = delayHP1[i - 1];
    }

    for (i = 15; i > 0; i--)
    {
        delayHP2[i] = delayHP2[i - 1];
    }

    // Save HP outputs into delays
    delayHP1[0] = yhp1;
    delayHP2[0] = yhp2;

    return b;
}

/*
 * Implements a 19. degree WDF
 */
double wdf19deg(double x, double* delays2T, double* delayT, int n, double* yhp)
{
    // Variables for Adaptor out and inputs
    double b1, b2, a1;

    // interim results
    double yUpper = 0, yLower = 0;

    int sz2Tdelay = (1 << n);
    int szTdelay= sz2Tdelay / 2;

    /****** Upper half ******/
    a1 = x;

    // calculate adaptors
    int i = 0, j = 0;
    for (i = 0; i < 4; i++)
    {
        if (i < 1)
        {
            twoPortCrossAdaptor(alphas[i], a1, delays2T[i*sz2Tdelay + (sz2Tdelay-1)], &b1, &b2);        // delays2T[i*sz2Tdelay + (sz2Tdelay-1)] == delays2T[i][sz2Tdelay-1] (hopefully...)
        }
        else
        {
            twoPortAdaptor(alphas[i], a1, delays2T[i*sz2Tdelay + (sz2Tdelay-1)], &b1, &b2);
        }
        // Shift |2T| delay values
        for (j = sz2Tdelay - 1; j > 0; j--)
        {
            delays2T[i*sz2Tdelay + j] = delays2T[i*sz2Tdelay + (j-1)]; // delays2T[i][j] = delays2T[i][j-1]
        }
        delays2T[i*sz2Tdelay + 0] = b2; // delays2T[i][0] = b2
        a1 = b1;
    }

    // Output of upper branch
    yUpper = delayT[szTdelay - 1];

    // Shift |T| delay
    for (j = szTdelay - 1; j > 0; j--)
    {
        delayT[j] = delayT[j - 1];
    }
    delayT[0] = b1;

    /****** Lower half ******/
    a1 = x;

    // calculate adaptors
    for (i = 5; i < 10; i++)
    {
        if (i < 7)
        {
            twoPortCrossAdaptor(alphas[i-1], a1, delays2T[i*sz2Tdelay + (sz2Tdelay-1)], &b1, &b2);
        }
        else
        {
            twoPortAdaptor(alphas[i-1], a1, delays2T[i*sz2Tdelay + (sz2Tdelay-1)], &b1, &b2);
        }
        // Shift |2T| delay values
        for (j = sz2Tdelay - 1; j > 0; j--)
        {
            delays2T[i*sz2Tdelay + j] = delays2T[i*sz2Tdelay + (j - 1)]; // delays2T[i][j] = delays2T[i][j-1]
        }
        delays2T[i*sz2Tdelay + 0] = b2; // delays2T[i][0] = b2
        a1 = b1;
    }

    // Output of lower branch
    yLower = b1;

    *yhp = (0.5 * (-yUpper + yLower));

    return (0.5 * (yUpper + yLower));
}

// Debugging purpose
double calcSingleWdf19deg(double x)
{
    double yhp;

    return wdf19deg(x, delay2T_1[0], delayT_1, 1, &yhp);
}


/*
 * Calculate a two-port adaptor with crossed output side
 */
 // TODO: Type of alpha?
void twoPortCrossAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2)
{
    // TODO: Not sure of sign of inA1 and alpha here (they differ in Gaszi document in different figures)
    double firstAdder = -inA1 + inA2;

    // Calculate outputs
    *outB1 = (alpha * firstAdder) + (-1) * inA2;
    *outB2 = firstAdder + (*outB1);
}

/*
 * Calculate a two-port adaptor
 */
 // TODO: Type of alpha?
void twoPortAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2)
{
    // TODO: Not sure of sign of inA1 and alpha here (they differ in Gaszi document in different figures)
    double firstAdder = -inA1 + inA2;

    // Calculate outputs
    *outB2 = (alpha * firstAdder) + (-1) * inA2;
    *outB1 = ((-1) * firstAdder) + (*outB2);
}

/*
 * Helper functions
 */
void init2dArray(double* array, int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            array[i*cols+j] = 0; // array[i][j] = 0
        }
    }
}

void initArray(double* array, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        array[i] = 0;
    }
}
