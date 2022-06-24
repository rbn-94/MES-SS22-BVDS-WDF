//-----------------------------------------------------------
// Digital Signal Processing  Lab
// Testprogram Interrupt

#include "subroutines.h"
#include "wdf19deg.h"

#define false 0
#define true 1

volatile Uint32 timertick;
short count_INT=0;
AIC_data AnalogIn;

volatile short inData = 0;
volatile short outData = 0;

volatile Bool newSampleAvailable = false;

interrupt void int_Timer0(){
	DSK6713_LED_on(1);
}
interrupt void intser_McBSP0()
{
	AnalogIn.l_r = MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data
	inData = AnalogIn.channel[LEFT];

	newSampleAvailable = true;
}

void main()
{
	float dInput = 0.0;
	float dOutput = 0.0;

	initDelays();

	c6713_dsk_init(); 				//init DSK, codec, McBSP
	mcbsp_start();					//start Audioport
	mcbsp_int_init();				//init MSBSP Interrupt

	DSK6713_LED_off(1);				//l�sche LED
	while(1)
	{
		if(newSampleAvailable)
		{
			dInput = (float)((float)inData / 32768);
			dOutput = octaveFilterbank(dInput);
			//dOutput = calcSingleWdf19deg(dInput);
			outData = (short)(dOutput * 32768);
			output_sample(outData);   					//output 32 bit data, LEFT and RIGHT

			newSampleAvailable = false;
		}
	}
}
