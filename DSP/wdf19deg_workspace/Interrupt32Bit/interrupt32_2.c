//-----------------------------------------------------------
// Digital Signal Processing  Lab
// Testprogram Interrupt


//#include "fft.h"
#include "subroutines.h"
#include "wdf19deg.h"

#define false 0
#define true 1

volatile Uint32 timertick;
short count_INT=0;
AIC_data AnalogIn;

short inData = 0;
short outData = 0;
double dInput = 0;
double dOutput = 0;

Bool newSampleAvailable = false;

//set sampling rate

interrupt void int_Timer0(){
	DSK6713_LED_on(1);
}
interrupt void intser_McBSP0()
{
	AnalogIn.l_r = MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data
	//output_sample(AnalogIn.l_r );   					//output 32 bit data, LEFT and RIGHT

	//value[bufnr][step].re=AnalogIn.channel[LEFT];
	//value[bufnr][step].im=0;

	// TODO: Left or Right or both channels?
	inData = AnalogIn.channel[LEFT];

	newSampleAvailable = true;
}


void main()
{
	c6713_dsk_init(); 				//init DSK, codec, McBSP
	mcbsp_start();					//start Audioport
	mcbsp_int_init();				//init MSBSP Interrupt

	timer0init();					//init T0 period
	timer0_int_init();				//init T0 interrupt (Realtime check)
	TIMER_start(Timer0handle);		//start Timer0
	timer1init();					//init T1 period (profile timer)
	DSK6713_LED_off(1);				//lösche LED
	while(1)
	{
		/*---------Realtime test-------------*/
		TIMER_start(Timer0handle);					//start Timer

		/*-----------------------------------*/
		if(newSampleAvailable)
		{
			dInput = (double)((double)inData / 32768);
			dOutput = wdf19deg(dInput);
			outData = (short)(dOutput * 32768);
			output_sample(outData);   					//output 32 bit data, LEFT and RIGHT

			newSampleAvailable = false;
		}
//		/*---------Realtime test-------------*/
//			TIMER_start(Timer0handle);					//start Timer
//			DSK6713_LED_off(1);							//lösche LED
//		/*-----------------------------------*/

	}
}

