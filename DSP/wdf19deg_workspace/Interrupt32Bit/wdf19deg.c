/**
 * @author Robin Franzen
 * @email robin.franzen94@gmail.com
 * @create date 2022-05-21 12:27:11
 * @modify date 2022-05-21 12:27:11
 * @desc DSP code for wave digital filter of 19. degree
 */

#include "wdf19deg.h"

/* Globals for delays T and 2T */
double upper2T[4][2]       = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
double upperT              = 0;

double lower2T[5][2]       = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

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

/* Prototypes */
void twoPortCrossAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2);
void twoPortAdaptor(double alpha, double inA1, double inA2, double* outB1, double* outB2);

/*
 * Implements a 19. degree WDF  
 */
#if 0
double wdf19deg(double x)
{
	// Variables for Adaptor out and inputs
	double b1, b2, a1;

	a1 = x;

	twoPortCrossAdaptor(alphas[0], a1, upper2T[0][1], &b1, &b2);

	// Shift delay values
	upper2T[0][1] = upper2T[0][0];
	upper2T[0][0] = b2;

	return b1;
}
#endif

#if 1
double wdf19deg(double x)
{
    // Variables for Adaptor out and inputs
	double b1, b2, a1;

    // interim results
	double yUpper = 0, yLower = 0;

    /****** Upper half ******/
    a1 = x;

    // calculate adaptors
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (i < 1)
        {
            twoPortCrossAdaptor(alphas[i], a1, upper2T[i][1], &b1, &b2);
        }
        else
        {
            twoPortAdaptor(alphas[i], a1, upper2T[i][1], &b1, &b2);
        }
        // Shift delay values
        upper2T[i][1] = upper2T[i][0];
        upper2T[i][0] = b2;
        a1 = b1;
    }

    // Output of upper branch
    yUpper = upperT;
    upperT = b1;

    /****** Lower half ******/
    a1 = x;

    // calculate adaptors
    for (i = 0; i < 5; i++)
    {
        if (i < 2)
        {
            twoPortCrossAdaptor(alphas[4+i], a1, lower2T[i][1], &b1, &b2);
        }
        else
        {
            twoPortAdaptor(alphas[4+i], a1, lower2T[i][1], &b1, &b2);
        }        
        // Shift delay values
        lower2T[i][1] = lower2T[i][0];
        lower2T[i][0] = b2;
        a1 = b1;
    } 

    // Output of lower branch
    yLower = b1;

    return (0.5 * (yUpper + yLower));
}
#endif

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
