//-----------------------------------------------------------
// Digital Signal Processing  Lab
// Testprogram Interrupt


#include "fft.h"
#include "subroutines.h"


volatile Uint32 timertick;
// two buffers for input and output samples with two counters
	short inBuf_L;
	short inBuf_R;
	short count_INT=0;
	AIC_data AnalogIn;

	//set sampling rate



interrupt void int_Timer0(){
		DSK6713_LED_on(1);
}
interrupt void intser_McBSP0(){
	static Uint16 step=0;
	static complex value[N];
	AnalogIn.l_r = MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data
	output_sample(AnalogIn.l_r);   					//output 32 bit data, LEFT and RIGHT
	/*---------Realtime test-------------*/
	TIMER_start(Timer0handle);					//start Timer
	DSK6713_LED_off(1);							//lösche LED
	/*-----------------------------------*/
	value[step].re=AnalogIn.channel[LEFT];
	value[step].im=0;
	step=(step+1);
	if(step>=N){
		fft(N, &value[0],1,1);
		step=0;
	}
	/*---------Realtime test-------------*/
	TIMER_start(Timer0handle);					//start Timer
	DSK6713_LED_off(1);							//lösche LED
	/*-----------------------------------*/
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

	while(1){

	}
}

