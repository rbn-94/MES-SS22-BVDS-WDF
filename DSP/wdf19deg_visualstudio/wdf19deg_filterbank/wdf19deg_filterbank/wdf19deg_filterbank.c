#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "wdf19deg.h"

#define N 1000

#define ROWS 4
#define COLS 6

#define GAIN 1

double xSample[N];
double y[N];

double testArray2d[ROWS][COLS] = {
	{0, 0, 4, 2, 0, 8},
	{0, 0, 9, 1, 0, 0},
	{0, 0, 0, 0, 0, 1},
	{1, 0, 0, 3, 0, 0}
};


// Prototypes
void createImpulse();
void createSinus();
double shift2dArrayRowbyRow(double* array2d, int cols, int rows);


int main()
{
	printf("Hello World");

	for (int i = 0; i < 3; i++)
	{
		shift2dArrayRowbyRow(testArray2d[0], COLS, ROWS);
	}

	initDelays();

	//createImpulse();
	createSinus();

	for (int i = 0; i < N; i++)
	{
		y[i] = octaveFilterbank(xSample[i]) * GAIN;
		//y[i] = calcSingleWdf19deg(xSample[i]);
	}

	return 0;
}

void createImpulse()
{
	xSample[0] = 1.0;

	for (int i = 1; i < N; i++)
	{
		xSample[i] = 0;
	}
}

void createSinus()
{
	int f = 1000;
	int fs = 48000;

	double m_phase = 0.0;
	double phaseInc = 2 * M_PI * (double)f / fs;

	for (int i = 0; i < N; i++)
	{
		xSample[i] = sin(m_phase);
		m_phase = m_phase + phaseInc;
	}
}


double shift2dArrayRowbyRow(double* array2d, int cols, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = cols - 1; j > 0; j--)
		{
			array2d[i * cols + j] = array2d[i * cols + (j - 1)]; // array2d[i][j] = array2d[i][j-1]
		}
		array2d[i * cols + 0] = 0;
	}	
	
}