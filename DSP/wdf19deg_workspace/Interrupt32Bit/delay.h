/*
 * delay.h
 *
 *  Created on: 07.06.2022
 *      Author: student
 */

#ifndef DELAY_H_
#define DELAY_H_

typedef struct Delay
{
	int length;
	int write;
	int read;
	float *buf;
} Delay;

void initDelay(Delay* d, int length);

Delay* createDelay(int length);

inline void delayPut(Delay *d, float value)
{

	d->buf[d->write] = value;
    d->write++;

	if (d->write == d->length) 
		d->write = 0;
}

inline float delayGet(Delay *d)
{
	float item = d->buf[d->read];
	d->read++;
	if (d->read == d->length) 
		d->read = 0;
	return item;
}

#endif /* DELAY_H_ */
