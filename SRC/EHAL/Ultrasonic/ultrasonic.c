/*
 * ultrasonic.c
 *
 *  Created on: Feb 28, 2022
 *      Author: MahmoudLabib
 */

#include "ultrasonic.h"
#include <util/delay.h>
#include <avr/io.h>

ICU_ConfigType config= {RISING_Edge,F_CPU_8};
static volatile uint8 g_edgeCount = 0;
static volatile uint16 g_timeHigh = 0;
static volatile uint16 distance =0;



void Ultrasonic_init(void){
	GPIO_setPinDir(PORTB_ID, PIN5_ID, OUTPUT_PIN);

	ICU_Init(&config);
	ICU_SetCallBack(&Ultrasonic_edgeProcessing);

}


void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID, PIN5_ID, logic_high);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, logic_low);
}


uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	distance =(uint16)(((float32)g_timeHigh / 57.5));
	return distance ;//(uint16)(((float32)(g_timeHigh/2)*(343))/1000);
}



void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_ClearTimerValue();
		/* Detect falling edge */
		ICU_SetEdgeDetectionType(FALLING_Edge);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_GetInputCaptureValue();
		/* Detect rising edge */
		ICU_SetEdgeDetectionType(RISING_Edge);
		g_edgeCount=0;
	}


}
