/*C6713dskinit.h Include file for C6713DSK.C */
#ifndef C6713DSKINITH
#define C6713DSKINITH
#include "dsk6713.h"
#include "dsk6713_aic23.h"			/*codec-DSK support file*/
#include "dsk6713_led.h"
#include <csl_edma.h>
#define N 256

#define LEFT  1                  /*data structure for union of 32-bit data*/
#define RIGHT 0                  /*into two 16-bit data*/
#define TCCINTNUM   10			 /*edma int num*/

//#define  int_driven                /*don't wait for mcbsp ready in input_sample()*/
//#define fs = DSK6713_AIC23_FREQ_48KHZ;

typedef union {
	Uint32 l_r;
	short channel[2];
} AIC_data;

extern Uint32 fs;            			//for sampling frequency
extern Uint32 CODECEventId;
extern short pingpong;
extern short newdata;
extern AIC_data inbuf1[N],inbuf2[N];

extern TIMER_Handle Timer0handle,Timer1handle;
extern EDMA_Handle hEdmaRec,hEdmaRec1,hEdmaRec2;     /* Handle and Reload Handle for EDMA receive */
extern MCBSP_Config AIC23CfgData;
extern DSK6713_AIC23_Config config;





/*  Function Prototypes */

void c6713_dsk_init(); /*Initialisation functions*/
void timer0init();
void timer1init();
void initEdma(void);


void timer0_int_init();/*Interrupt initialisation*/
void mcbsp_int_init();
void edma_int_init(void);

void mcbsp_start();	  /*start functions*/
void timer_start(int nr);

void output_sample(int);
void output_left_sample(short);
void output_right_sample(short);
Uint32 input_sample();
short input_left_sample();
short input_right_sample();
void stopEdma(void); /* function used to stop EDMA */


//#include "C6713dskinit.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//#include <csl.h>
//#include <csl_cache.h>
//#include <csl_edma.h>
//#include <csl_timer.h>
//#include <csl_mcbsp.h>
//#include <csl_irq.h>
//#include <dsk6713.h>
//#include <dsk6713_aic23.h>





#endif
