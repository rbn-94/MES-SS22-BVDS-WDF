/*
 * wdf19deg.h
 *
 *  Created on: 24.05.2022
 *      Author: student
 */

#ifndef WDF19DEG_H_
#define WDF19DEG_H_

#include "delay.h"

void initDelays();

float octaveFilterbank(float x);

float calcSingleWdf19deg(float x);

#endif /* WDF19DEG_H_ */
