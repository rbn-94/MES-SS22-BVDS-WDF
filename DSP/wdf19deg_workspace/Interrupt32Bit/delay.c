/*
 * delay.c
 *
 *  Created on: 07.06.2022
 *      Author: student
 */
#include "stdlib.h"

#include "delay.h"

#include "subroutines.h"

void initDelay(Delay* d, int length)
{
	d->buf = (float*)calloc(length, sizeof(float));

	// Init circular delay buffer with zeros and set read pointer to last position
	d->length = length;
	d->read =  0;
	d->write = 0;
}

Delay* createDelay(int length)
{
	Delay* d;
	d = (Delay*)malloc(sizeof(Delay));
	d->buf = (float*)calloc(length, sizeof(float));
	d->length = length;
	d->read =  0;
	d->write = 0;

	return d;
}
