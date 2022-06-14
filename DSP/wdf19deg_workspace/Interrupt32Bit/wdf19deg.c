/**
 * @author Robin Franzen
 * @email robin.franzen94@gmail.com
 * @create date 2022-05-21 12:27:11
 * @modify date 2022-05-21 12:27:11
 * @desc DSP code for wave digital filter of 19. degree
 */

#include "wdf19deg.h"
#include "subroutines.h"

#define NUM_DELAY_BLOCKS 9

 /* Coefficients */
float alphas[9] = {
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

float weights[6] = {
		1.0,
        1.0,
        1.0,
        1.0,
        1.0,
        1.0
};

/* Globals for delays T and 2T */
Delay delay2T_1[NUM_DELAY_BLOCKS];
Delay delay2T_2[NUM_DELAY_BLOCKS];
Delay delay2T_3[NUM_DELAY_BLOCKS];
Delay delay2T_4[NUM_DELAY_BLOCKS];
Delay delay2T_5[NUM_DELAY_BLOCKS];

Delay delayT_1;
Delay delayT_2;
Delay delayT_3;
Delay delayT_4;
Delay delayT_5;

/* Globals for HP output delays T */
Delay delayHP1;
Delay delayHP2;
Delay delayHP3;
Delay delayHP4;

Uint32 timer_cnt = 0;

/* Prototypes */
inline void twoPortCrossAdaptor(float alpha, float inA1, float inA2, float* outB1, float* outB2);
inline void twoPortAdaptor(float alpha, float inA1, float inA2, float* outB1, float* outB2);
float wdf19deg(float x, Delay delay2T[NUM_DELAY_BLOCKS], Delay* delayT, float* yhp);

void initDelays()
{
	// -|2T|- Delays
	int i = 0;
	for (i = 0; i < NUM_DELAY_BLOCKS; i++)
	{
		initDelay(&delay2T_1[i], 2);
	}

	for (i = 0; i < NUM_DELAY_BLOCKS; i++)
	{
		initDelay(&delay2T_2[i], 4);
	}

	for (i = 0; i < NUM_DELAY_BLOCKS; i++)
	{
		initDelay(&delay2T_3[i], 8);
	}

	for (i = 0; i < NUM_DELAY_BLOCKS; i++)
	{
		initDelay(&delay2T_4[i], 16);
	}

	for (i = 0; i < NUM_DELAY_BLOCKS; i++)
	{
		initDelay(&delay2T_5[i], 32);
	}

	// -|T|- Delays
	initDelay(&delayT_1, 1);
	initDelay(&delayT_2, 2);
	initDelay(&delayT_3, 4);
	initDelay(&delayT_4, 8);
	initDelay(&delayT_5, 16);

	// Output delays
	initDelay(&delayHP1, 120);
	initDelay(&delayHP2, 112);
	initDelay(&delayHP3, 96);
	initDelay(&delayHP4, 64);
}

float octaveFilterbank(float x)
{
    float yhp1, yhp2, yhp3, yhp4, yhp5;
    float ytp1, ytp2, ytp3, ytp4, ytp5;
    float b = 0.0;

    float yHP1, yHP2, yHP3, yHP4;

    ytp1 = wdf19deg(x,    delay2T_1, &delayT_1, &yhp1);
    ytp2 = wdf19deg(ytp1, delay2T_2, &delayT_2, &yhp2);
    ytp3 = wdf19deg(ytp2, delay2T_3, &delayT_3, &yhp3);
    ytp4 = wdf19deg(ytp3, delay2T_4, &delayT_4, &yhp4);
    ytp5 = wdf19deg(ytp4, delay2T_5, &delayT_5, &yhp5);

    yHP1 = delayGet(&delayHP1);
    yHP2 = delayGet(&delayHP2);
    yHP3 = delayGet(&delayHP3);
    yHP4 = delayGet(&delayHP4);

    // Calculate output
    b = (weights[0] * yHP1)  + (weights[1] * yHP2) + (weights[2] * yHP3) + (weights[3] * yHP4) + (weights[4] * yhp5) + (weights[5] * ytp5);

    delayPut(&delayHP1, yhp1);
    delayPut(&delayHP2, yhp2);
    delayPut(&delayHP3, yhp3);
    delayPut(&delayHP4, yhp4);

    return b;
}

/*
 * Implements a 19. degree WDF
 */
float wdf19deg(float x, Delay delay2T[NUM_DELAY_BLOCKS], Delay* delayT, float* yhp)
{
    // Variables for Adaptor out and inputs
    float uB1, uB2, uA1, lB1, lB2, lA1;

    // interim results
    float yUpper = 0, yLower = 0;

    uA1 = x;
    lA1 = x;

    int i = 0;
    for (i = 0; i < 5; i++)
    {
    	switch (i) {
			case 0:
				// Upper Branch
				twoPortCrossAdaptor(alphas[i], uA1, delayGet(&delay2T[i]), &uB1, &uB2);
				delayPut(&delay2T[i], uB2);
				uA1 = uB1;

				// Lower Branch
				twoPortCrossAdaptor(alphas[i+4], lA1, delayGet(&delay2T[i+4]), &lB1, &lB2);
				delayPut(&delay2T[i+4], lB2);
				lA1 = lB1;
				break;
			case 1:
				// Upper branch
				twoPortAdaptor(alphas[i], uA1, delayGet(&delay2T[i]), &uB1, &uB2);
				delayPut(&delay2T[i], uB2);
				uA1 = uB1;

				// Lower branch
				twoPortCrossAdaptor(alphas[i+4], lA1, delayGet(&delay2T[i+4]), &lB1, &lB2);
				delayPut(&delay2T[i+4], lB2);
				lA1 = lB1;
				break;

			case 4:
				// Upper branch
				yUpper = delayGet(delayT);
				delayPut(delayT, uB1);

				// Lower branch
				twoPortAdaptor(alphas[i+4], lA1, delayGet(&delay2T[i+4]), &lB1, &lB2);
				delayPut(&delay2T[i+4], lB2);
				yLower = lB1;
				break;
			default:
				// Upper branch
				twoPortAdaptor(alphas[i], uA1, delayGet(&delay2T[i]), &uB1, &uB2);
				delayPut(&delay2T[i], uB2);
				uA1 = uB1;

				// Lower Branch
				twoPortAdaptor(alphas[i+4], lA1, delayGet(&delay2T[i+4]), &lB1, &lB2);
				delayPut(&delay2T[i+4], lB2);
				lA1 = lB1;
				break;
		}
    }

    *yhp = ((yLower - yUpper) / 2);

    return ((yUpper + yLower) / 2);
}

float calcSingleWdf19deg(float x)
{
    float yhp;

    return wdf19deg(x, delay2T_1, &delayT_1, &yhp);
}

/*
 * Calculate a two-port adaptor with crossed output side
 */
inline void twoPortCrossAdaptor(float alpha, float inA1, float inA2, float* outB1, float* outB2)
{
    *outB1 = (alpha * (inA2 - inA1)) - inA2;
    *outB2 = inA2 - inA1 + (*outB1);
}

/*
 * Calculate a two-port adaptor
 */
inline void twoPortAdaptor(float alpha, float inA1, float inA2, float* outB1, float* outB2)
{
    *outB2 = (alpha * (inA2 - inA1)) - inA2;
    *outB1 = (*outB2) - (inA2 - inA1) ;
}
