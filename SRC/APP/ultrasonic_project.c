/*
 * ultrasonic_project.c
 *
 *  Created on: Mar 1, 2022
 *      Author: MahmoudLabib
 */


#include "../EHAL/Ultrasonic/ultrasonic.h"
#include "../EHAL/LCD/lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void mini_project4(){
    uint16 data =0;
	sei();
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance= ");
	while(1){

		//Ultrasonic_Trigger();
		data =Ultrasonic_readDistance();
		LCD_moveCursor(0, 10);
		LCD_intgerToString(data);
		LCD_displayString(" CM ");

	}

}
