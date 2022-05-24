/*
 * fixed.c
 *
 *  Created on: 24.05.2022
 *      Author: student
 */

#include "fixed.h"

fixed fixmul(fixed a,fixed b)
{
	return((a*b)>>15);
}
fixed fixsqrt(fixed a)
{
	return(sqrt(a)* zweihoch75);
}



