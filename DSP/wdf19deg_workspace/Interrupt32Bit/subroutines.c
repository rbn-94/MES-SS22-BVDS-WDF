#include "subroutines.h"
//#define int_driven				    /*uncomment to initialise the AIC interface interrupt driven*/

//MCBSP_Config AIC23CfgData = {		/*configuration of the MCBSP Port*/
//        MCBSP_FMKS(SPCR, FREE, NO)              |
//        MCBSP_FMKS(SPCR, SOFT, NO)              |
//        MCBSP_FMKS(SPCR, FRST, YES)             |
//        MCBSP_FMKS(SPCR, GRST, YES)             |
//        MCBSP_FMKS(SPCR, XINTM, XRDY)           |
//        MCBSP_FMKS(SPCR, XSYNCERR, NO)          |
//        MCBSP_FMKS(SPCR, XRST, YES)             |
//        MCBSP_FMKS(SPCR, DLB, OFF)              |
//        MCBSP_FMKS(SPCR, RJUST, RZF)            |
//        MCBSP_FMKS(SPCR, CLKSTP, DISABLE)       |
//        MCBSP_FMKS(SPCR, DXENA, OFF)            |
//        MCBSP_FMKS(SPCR, RINTM, RRDY)           |
//        MCBSP_FMKS(SPCR, RSYNCERR, NO)          |
//        MCBSP_FMKS(SPCR, RRST, YES),
//
//        MCBSP_FMKS(RCR, RPHASE, SINGLE)         |
//        MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
//        MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)       |
//        MCBSP_FMKS(RCR, RCOMPAND, MSB)          |
//        MCBSP_FMKS(RCR, RFIG, NO)               |
//        MCBSP_FMKS(RCR, RDATDLY, 0BIT)          |
//        MCBSP_FMKS(RCR, RFRLEN1, OF(0))         | // This changes to 1 FRAME
//        MCBSP_FMKS(RCR, RWDLEN1, 32BIT)         | // This changes to 32 bits per frame
//        MCBSP_FMKS(RCR, RWDREVRS, DISABLE),
//
//        MCBSP_FMKS(XCR, XPHASE, SINGLE)         |
//        MCBSP_FMKS(XCR, XFRLEN2, DEFAULT)       |
//        MCBSP_FMKS(XCR, XWDLEN2, DEFAULT)       |
//        MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
//        MCBSP_FMKS(XCR, XFIG, NO)               |
//        MCBSP_FMKS(XCR, XDATDLY, 0BIT)          |
//        MCBSP_FMKS(XCR, XFRLEN1, OF(0))         | // This changes to 1 FRAME
//        MCBSP_FMKS(XCR, XWDLEN1, 32BIT)         | // This changes to 32 bits per frame
//        MCBSP_FMKS(XCR, XWDREVRS, DISABLE),
//
//        MCBSP_FMKS(SRGR, GSYNC, DEFAULT)        |
//        MCBSP_FMKS(SRGR, CLKSP, DEFAULT)        |
//        MCBSP_FMKS(SRGR, CLKSM, DEFAULT)        |
//        MCBSP_FMKS(SRGR, FSGM, DEFAULT)         |
//        MCBSP_FMKS(SRGR, FPER, DEFAULT)         |
//        MCBSP_FMKS(SRGR, FWID, DEFAULT)         |
//        MCBSP_FMKS(SRGR, CLKGDV, DEFAULT),
//
//        MCBSP_MCR_DEFAULT,
//        MCBSP_RCER_DEFAULT,
//        MCBSP_XCER_DEFAULT,
//
//        MCBSP_FMKS(PCR, XIOEN, SP)              |
//        MCBSP_FMKS(PCR, RIOEN, SP)              |
//        MCBSP_FMKS(PCR, FSXM, EXTERNAL)         |
//        MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
//        MCBSP_FMKS(PCR, CLKXM, INPUT)           |
//        MCBSP_FMKS(PCR, CLKRM, INPUT)           |
//        MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
//        MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
//        MCBSP_FMKS(PCR, FSXP, ACTIVEHIGH)       |
//        MCBSP_FMKS(PCR, FSRP, ACTIVEHIGH)       |
//        MCBSP_FMKS(PCR, CLKXP, FALLING)         |
//        MCBSP_FMKS(PCR, CLKRP, RISING)
//    };
/*MCBSP Konfiguration*/
MCBSP_Config AIC23CfgData = {
        MCBSP_FMKS(SPCR, FREE, NO)              |
        MCBSP_FMKS(SPCR, SOFT, NO)              |
        MCBSP_FMKS(SPCR, FRST, YES)             |
        MCBSP_FMKS(SPCR, GRST, YES)             |
        MCBSP_FMKS(SPCR, XINTM, XRDY)           |
        MCBSP_FMKS(SPCR, XSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, XRST, YES)             |
        MCBSP_FMKS(SPCR, DLB, OFF)              |
        MCBSP_FMKS(SPCR, RJUST, RZF)            |
        MCBSP_FMKS(SPCR, CLKSTP, DISABLE)       |
        MCBSP_FMKS(SPCR, DXENA, OFF)            |
        MCBSP_FMKS(SPCR, RINTM, RRDY)           |
        MCBSP_FMKS(SPCR, RSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, RRST, YES),

        MCBSP_FMKS(RCR, RPHASE, SINGLE)         |
        MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RCOMPAND, MSB)          |
        MCBSP_FMKS(RCR, RFIG, NO)               |
        MCBSP_FMKS(RCR, RDATDLY, 0BIT)          |
        MCBSP_FMKS(RCR, RFRLEN1, OF(0))         | // This changes to 1 FRAME
        MCBSP_FMKS(RCR, RWDLEN1, 32BIT)         | // This changes to 32 bits per frame
        MCBSP_FMKS(RCR, RWDREVRS, DISABLE),

        MCBSP_FMKS(XCR, XPHASE, SINGLE)         |
        MCBSP_FMKS(XCR, XFRLEN2, DEFAULT)       |
        MCBSP_FMKS(XCR, XWDLEN2, DEFAULT)       |
        MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
        MCBSP_FMKS(XCR, XFIG, NO)               |
        MCBSP_FMKS(XCR, XDATDLY, 0BIT)          |
        MCBSP_FMKS(XCR, XFRLEN1, OF(0))         | // This changes to 1 FRAME
        MCBSP_FMKS(XCR, XWDLEN1, 32BIT)         | // This changes to 32 bits per frame
        MCBSP_FMKS(XCR, XWDREVRS, DISABLE),

        MCBSP_FMKS(SRGR, GSYNC, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSP, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSM, DEFAULT)        |
        MCBSP_FMKS(SRGR, FSGM, DEFAULT)         |
        MCBSP_FMKS(SRGR, FPER, DEFAULT)         |
        MCBSP_FMKS(SRGR, FWID, DEFAULT)         |
        MCBSP_FMKS(SRGR, CLKGDV, DEFAULT),

        MCBSP_MCR_DEFAULT,
        MCBSP_RCER_DEFAULT,
        MCBSP_XCER_DEFAULT,

        MCBSP_FMKS(PCR, XIOEN, SP)              |
        MCBSP_FMKS(PCR, RIOEN, SP)              |
        MCBSP_FMKS(PCR, FSXM, EXTERNAL)         |
        MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
        MCBSP_FMKS(PCR, CLKXM, INPUT)           |
        MCBSP_FMKS(PCR, CLKRM, INPUT)           |
        MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
        MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
        MCBSP_FMKS(PCR, FSXP, ACTIVEHIGH)       |
        MCBSP_FMKS(PCR, FSRP, ACTIVEHIGH)       |
        MCBSP_FMKS(PCR, CLKXP, FALLING)         |
        MCBSP_FMKS(PCR, CLKRP, RISING)
    };
DSK6713_AIC23_Config config = { 		   /*AIC23 configuration*/           \
    0x001C,  /* 0 DSK6713_AIC23_LEFTINVOL  Left line input channel volume */ \
    0x001C,  /* 1 DSK6713_AIC23_RIGHTINVOL Right line input channel volume */\
    0x00d8,  /* 2 DSK6713_AIC23_LEFTHPVOL  Left channel headphone volume */  \
    0x00d8,  /* 3 DSK6713_AIC23_RIGHTHPVOL Right channel headphone volume */ \
    0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      \
    0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     \
    0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             \
    0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ \
    0x0081,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control */            \
    0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   \
};
/*-- EDMA Konfiguration für MCBSP READ --- */
EDMA_Config cfgEdmaRec1 = {
		EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

				EDMA_OPT_PRI_HIGH,    /* Priority levels for EDMA events:-
                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

				EDMA_OPT_ESIZE_32BIT,/* Element size :-
                             EDMA_OPT_ESIZE_32BIT - 32 bit word
                             EDMA_OPT_ESIZE_16BIT - 16 bit word
                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

				EDMA_OPT_2DS_NO,     /* Source dimension :-
                             EDMA_OPT_2DS_NO  - 1-dimensional source
                             EDMA_OPT_2DS_YES - 2-dimensional source         */

				EDMA_OPT_SUM_NONE,   /* Source address update mode :-
                             EDMA_OPT_SUM_NONE - Fixed address mode
                             EDMA_OPT_SUM_INC  - Increment address mode
                             EDMA_OPT_SUM_DEC  - Decrement address mode
                             EDMA_OPT_SUM_IDX  - Address modified by element
                                                 index or frame Index        */
				EDMA_OPT_2DD_NO,     /* Destination dimension :-
                             EDMA_OPT_2DD_NO   - 1-dimensional source
                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

				EDMA_OPT_DUM_INC,    /* Destination address update mode :-
                             EDMA_OPT_DUM_NONE - Fixed address mode
                             EDMA_OPT_DUM_INC  - Increment address mode
                             EDMA_OPT_DUM_DEC  - Decrement address mode
                             EDMA_OPT_DUM_IDX  - Address modified by element
                                                 index or frame Index        */

				EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
                             EDMA_OPT_TCINT_NO  - Indication disabled
                             EDMA_OPT_TCINT_YES - Indication enabled         */

				EDMA_OPT_TCC_OF(TCCINTNUM),/* Transfer complete code                     */

				EDMA_OPT_LINK_YES,   /* Linking of event parameters
                             EDMA_OPT_LINK_NO   -  Disabled
                             EDMA_OPT_LINK_YES  -  Enabled                   */

				EDMA_OPT_FS_NO       /* Frame synchronization
                             EDMA_OPT_FS_NO  - Channel is element/array
                                                synchronized
                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
		),
		EDMA_SRC_OF(NULL),	/* Source address register
                               &MCBSP DRR-Register   - source address                */

		EDMA_CNT_OF(N),   /* Transfer count parameter
                                BUFF_SZ      - buffer sizes in # of ints     */

		EDMA_DST_OF(inbuf1),      /* Destination address parameter
                                 ping - destination address                  */

		EDMA_IDX_OF(0x00000004),/* Index parameter                                 */

		EDMA_RLD_OF(0x00000000) /* Count reload/link parameter                     */
};

EDMA_Config cfgEdmaRec2= {
		EDMA_OPT_RMK(          /* Making Options parameter register - EDMA_OPT    */

				EDMA_OPT_PRI_HIGH,    /* Priority levels for EDMA events:-
                             EDMA_OPT_PRI_LOW  - Low priority EDMA transfer
                             EDMA_OPT_PRI_HIGH - High priority EDMA transfer*/

				EDMA_OPT_ESIZE_32BIT,/* Element size :-
                             EDMA_OPT_ESIZE_32BIT - 32 bit word
                             EDMA_OPT_ESIZE_16BIT - 16 bit word
                             EDMA_OPT_ESIZE_8BIT  -  8 bit word              */

				EDMA_OPT_2DS_NO,     /* Source dimension :-
                             EDMA_OPT_2DS_NO  - 1-dimensional source
                             EDMA_OPT_2DS_YES - 2-dimensional source         */

				EDMA_OPT_SUM_NONE,   /* Source address update mode :-
                             EDMA_OPT_SUM_NONE - Fixed address mode
                             EDMA_OPT_SUM_INC  - Increment address mode
                             EDMA_OPT_SUM_DEC  - Decrement address mode
                             EDMA_OPT_SUM_IDX  - Address modified by element
                                                 index or frame Index        */
				EDMA_OPT_2DD_NO,     /* Destination dimension :-
                             EDMA_OPT_2DD_NO   - 1-dimensional source
                             EDMA_OPT_2DD_YES  - 2-dimensional source        */

				EDMA_OPT_DUM_INC,    /* Destination address update mode :-
                             EDMA_OPT_DUM_NONE - Fixed address mode
                             EDMA_OPT_DUM_INC  - Increment address mode
                             EDMA_OPT_DUM_DEC  - Decrement address mode
                             EDMA_OPT_DUM_IDX  - Address modified by element
                                                 index or frame Index        */

				EDMA_OPT_TCINT_YES,  /* Transfer complete interrupt :-
                             EDMA_OPT_TCINT_NO  - Indication disabled
                             EDMA_OPT_TCINT_YES - Indication enabled         */

				EDMA_OPT_TCC_OF(TCCINTNUM),/* Transfer complete code                     */

				EDMA_OPT_LINK_YES,   /* Linking of event parameters
                             EDMA_OPT_LINK_NO   -  Disabled
                             EDMA_OPT_LINK_YES  -  Enabled                   */

				EDMA_OPT_FS_NO       /* Frame synchronization
                             EDMA_OPT_FS_NO  - Channel is element/array
                                                synchronized
                             EDMA_OPT_FS_YES -  Channel is frame synchronized*/
		),
		EDMA_SRC_OF(NULL),	/* Source address register
                               &MCBSP DRR-Register   - source address                */

		EDMA_CNT_OF(N),   /* Transfer count parameter
                                BUFF_SZ      - buffer sizes in # of ints     */

		EDMA_DST_OF(inbuf2),      /* Destination address parameter
                                 ping - destination address                  */

		EDMA_IDX_OF(0x00000004),/* Index parameter                                 */

		EDMA_RLD_OF(0x00000000) /* Count reload/link parameter                     */
};

DSK6713_AIC23_CodecHandle hAIC23_handle;
TIMER_Handle Timer0handle,Timer1handle;
Uint32 Timer0EventId;
Uint32 CODECEventId;

short pingpong=0;
short newdata=0;
AIC_data inbuf1[N],inbuf2[N];
EDMA_Handle hEdmaRec,hEdmaRec1,hEdmaRec2;  /* Handle and Reload Handle for EDMA receive */

TIMER_Config T0Config={
	0x02c4,	/*CTL-Reg : TSTAT,INVINP,CLKSRC,CP,HLD,GO,Reserved,PWID,DATIN,DATOUT,INVOUT,FUNC
			             0   ,0     , 1  ,  0 ,1  ,1  ,0       ,0   ,0    ,1       ,0   ,0 (0x2C4)*/
	N*0x0494,	/*PRD Register max counter value with clksrc 225 MHZ 1/48000=4/225.000.000 * count <=> count= 225.000.000/(48000*4) = 1172 <=> 0x494;*/
	0x0000	/* CNT actuell counter value*/

};
TIMER_Config T1Config={
	0x02c4,	/*CTL-Reg : TSTAT,INVINP,CLKSRC,CP,HLD,GO,Reserved,PWID,DATIN,DATOUT,INVOUT,FUNC
			             0   ,0     , 1  ,  0 ,1  ,1  ,0       ,0   ,0    ,1       ,0   ,0 (0x2C4)*/
	0xFFFFFFFF,	/*PRD Register max counter value with clksrc 225 MHZ 1/48000=4/225.000.000 * count <=> count= 225.000.000/(48000*4) = 1172 <=> 0x494;*/
	0x0000	/* CNT actuell counter value*/

};
void c6713_dsk_init(){       			//dsp-peripheral initialization
	DSK6713_init();                   	//call BSL to init DSK-EMIF,PLL)
	DSK6713_LED_init();					//initialise Leds
	hAIC23_handle=DSK6713_AIC23_openCodec(0, &config);//handle(pointer) to codec
	DSK6713_AIC23_setFreq(hAIC23_handle, DSK6713_AIC23_FREQ_48KHZ);  //set sample rate to 48 khz
	MCBSP_config(DSK6713_AIC23_DATAHANDLE,&AIC23CfgData);//interface 32 bits toAIC23
	//MCBSP_start(DSK6713_AIC23_DATAHANDLE, MCBSP_XMIT_START | MCBSP_RCV_START |
	//			MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);//start data channel again
}

void mcbsp_int_init(){						//init audiocodec interrupt
		IRQ_globalDisable();           		//disable interrupts
		CODECEventId=MCBSP_getRcvEventId(DSK6713_AIC23_codecdatahandle);//McBSP1 Recv
		IRQ_map(CODECEventId, 5);			//map McBSP1 Recv to INT5
		IRQ_reset(CODECEventId);    		//reset codec INT5
		IRQ_globalEnable();       			//globally enable interrupts
		IRQ_nmiEnable();          			//enable NMI interrupt
		IRQ_enable(CODECEventId);			//enable CODEC eventXmit INT5
}
void mcbsp_start(){
	MCBSP_start(DSK6713_AIC23_DATAHANDLE, MCBSP_XMIT_START | MCBSP_RCV_START |
				MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);//start data channel again
}
//init Timer (spru582)
	//CTL-Reg : TSTAT,INVINP,CLKSRC,CP,HLD,GO,Reserved,PWID,DATIN,DATOUT,INVOUT,FUNC
	//             0   ,0     ,1  ,  0 ,1  ,1  ,0       ,0   ,0    ,1       ,0   ,0 (0x2C4)
	//PRD Register max counter value with clksrc 225 MHZ 1/48000=4/225.000.000 * count <=> count= 225.000.000/(48000*4) = 1172 <=> 0x494;
	// CNT actuell counter value

	//Timer interrupt TINT0,TINT1 0x01,0x02
	//MUXH, MUXL multiplex Hard interrupt nr to soft interrupt vector (because 32 sources for only 12 interrupts 4-15) 0-3 are fixed Map T0->Int6
	// MUXL Bit 10-14 auf 1
	// MUXL x000 01xx xxxx xxxx Muxl = Muxl & ~(7c00) | 0x0400;
	//T0 default int14
void timer0init(){
	Timer0handle=TIMER_open(TIMER_DEV0, TIMER_OPEN_RESET);//open Timer0
	TIMER_config(Timer0handle, &T0Config);				  //configure Timer0
	//TIMER_start(Timer0handle);							  //start Timer
}														  //Interrupt section
void timer0_int_init(){
	IRQ_globalDisable();           		//disable interrupts
	Timer0EventId=TIMER_getEventId(Timer0handle);	//get Timer event ID
	IRQ_map(Timer0EventId, 4);					//map Timer0  to INT4
	IRQ_reset(Timer0EventId);    		//reset Timer0 INT5
	IRQ_globalEnable();       			//globally enable interrupts
	IRQ_nmiEnable();          			//enable NMI interrupt
	IRQ_enable(Timer0EventId);			//enable Timer0 event INT4

}
void timer1init(){
	Timer1handle=TIMER_open(TIMER_DEV1, TIMER_OPEN_RESET);//open Timer1
	TIMER_config(Timer1handle, &T1Config);				  //configure Timer1
}

void output_sample(int out_data){    //for out to Left and Right channels
	AIC_data SampleOut;
	SampleOut.l_r=0;                 //clear data structure
	SampleOut.l_r=out_data;          //32-bit data -->data structure

	while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));		//if ready to transmit
	MCBSP_write(DSK6713_AIC23_DATAHANDLE,SampleOut.l_r);//write/output data
}

Uint32 input_sample(){                      	  	//for 32-bit input
	AIC_data SampleIn;
#ifndef int_driven
	while(!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));//if ready to receive
#endif
	SampleIn.l_r=MCBSP_read(DSK6713_AIC23_DATAHANDLE);//read data
	return(SampleIn.l_r);
}






/************************************************************************\
name:      edma_int_init

 purpose:   Sets up interrupts to service EDMA transfers

 inputs:    void

 returns:   void
\************************************************************************/

void edma_int_init(void){
     //IRQ_setVecs(vectors);     /* point to the IRQ vector table	*/
	 IRQ_globalDisable();           		//disable interrupts
	 IRQ_map(IRQ_EVT_EDMAINT, 8);
	 IRQ_reset(IRQ_EVT_EDMAINT);
	 IRQ_enable(IRQ_EVT_EDMAINT);
	   EDMA_intDisable(TCCINTNUM);
	   EDMA_intClear(TCCINTNUM);
	   EDMA_intEnable(TCCINTNUM);
	 IRQ_nmiEnable();
     IRQ_globalEnable();
     //  /* Enable the related interrupts */
     //  IRQ_enable(IRQ_EVT_EDMAINT);
     //  EDMA_intDisable(TCCINTNUM);
     //  EDMA_intClear(TCCINTNUM);
     //  EDMA_intEnable(TCCINTNUM);
     //  /* Enable the EDMA channel */
     //  EDMA_enableChannel(hEdmaRec);
     //  EDMA_enableChannel(hEdmaXmt);
} /* End of SetInterruptsEdma() */



void initEdma(void){
	  EDMA_clearPram(0x00000000);
   /* Configure EDMA MCBSP XMT, REC  channel */

    //open EDMA MCBSP1 REC Event channel
    hEdmaRec = EDMA_open(EDMA_CHA_REVT1, EDMA_OPEN_RESET);
	   //open EDMA MCBSP1 XMT Event channel
    //hEdmaXmt = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_RESET);

  /* We also need two EDMA reload parameter sets so let's allocate them */
  /* here. Notice the -1, this means allocate any availale table.        */
  hEdmaRec1 = EDMA_allocTable(-1); //Reload Handle Receive
  hEdmaRec2 = EDMA_allocTable(-1); //Reload Handle Receive
  //get the Address of the MCBSP1 DRR-Register
   cfgEdmaRec1.src = MCBSP_getRcvAddr(DSK6713_AIC23_DATAHANDLE);
   cfgEdmaRec2.src = MCBSP_getRcvAddr(DSK6713_AIC23_DATAHANDLE);

  // Konfiguration dem handle zuweisen
    EDMA_config(hEdmaRec, &cfgEdmaRec1); //Receive
  // Konfiguration dem Reload handle zuweisen
    EDMA_config(hEdmaRec1,&cfgEdmaRec1); //Receive
    EDMA_config(hEdmaRec2, &cfgEdmaRec2); //Receive


  // link back to table start    //Receive
    EDMA_link(hEdmaRec,hEdmaRec2);
    EDMA_link(hEdmaRec2, hEdmaRec1);
    EDMA_link(hEdmaRec1, hEdmaRec2);

    EDMA_enableChannel(hEdmaRec);		//Enable DMAchannel
}

/************************************************************************\
 name:      stopEdma

 purpose:   Stops the EDMA service.

 inputs:    void

 returns:   void
\************************************************************************/
void stopEdma(void) {

    /*Disable interrupts, close EDMA channel before exit of the program*/
    IRQ_disable(IRQ_EVT_EDMAINT);
    EDMA_RSET(CCER,0x00000000);
    EDMA_disableChannel(hEdmaRec);
    EDMA_intDisable(TCCINTNUM);
    EDMA_intClear(TCCINTNUM);
 	EDMA_close(hEdmaRec);
 	EDMA_resetAll();
 	EDMA_RSET(CIPR,0xFFFFFFFF);
 	EDMA_RSET(ECR,0xFFFFFFFF);
}

