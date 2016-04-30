/*
 * 4_digit_seven_segment_display.c
 *
 * Created: 2016-04-28 8:40:28 PM
 * Author : Alvi
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>




#define segment_3 PC5 //Active LOW pin 16 
#define segment_4 PC4 //Active LOW pin 15
#define segment_2 PC3 //Active LOW pin 14
#define segment_6 PC2 //Active LOW pin 13
#define segment_1 PC1 //Active LOW pin 11
#define segment_7 PC0 //Active LOW pin 3
#define segment_5 PB2 //Active LOW pin 5

#define dotG_semi PB4 //Active LOW pin 13


#define digit_act1 PD0 //Active HIGH pin 1 
#define digit_act2 PD1 //Active HIGH pin 2
#define digit_act3 PD2 //Active HIGH pin 6
#define digit_act4 PD3 //Active HIGH pin 8 
#define dotI_act     //Active  HIGH pin 10  

#define dotE_act //Active HIGH  pin 1 
#define dotF_act //Active HIGH  pin 2 
#define dotG_act //ACtive HIGH pin 4
#define dotH_act //Active HIGH pin 6 
#define dotJ_act //Active HIGH pin 8 


#define dotE PD4 //Active LOW 
#define dotI //Active LOW pin 9   

#define datawire PD5 
#define latchwire PD6 
#define clockwire PD7

  
int main(void)
{	
	
 int i;
	
	DDRD |= (1 << digit_act1);  
	DDRD |= (1 << digit_act2);
	DDRD |= (1 << digit_act3); 
	DDRD |= (1 << digit_act4);  
	//Shift Register
	DDRD |= (1 << datawire); 
	DDRD |= (1 << latchwire); 
	DDRD |= (1 << clockwire);
	//
	DDRC |= (1 << segment_3);  
	DDRC |= (1 << segment_4);  
	DDRC |= (1 << segment_6);  
	DDRC |= (1 << segment_2); 
	DDRC |= (1 << segment_1);    
	DDRB |= (1 << segment_5);  
	DDRC |= (1 << segment_7);  
	
	PORTC |= (1 << segment_7);
	PORTC |= (1 << segment_6);
	PORTB |= (1 << segment_5); 
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_1);
 
	PORTD &= ~ (1 << datawire);
	PORTD &= ~ (1 << latchwire); 
	PORTD &= ~ (1 << clockwire);
	
	PORTD |= (1 << datawire);
	for (i = 0; i < 2; i ++){
		PORTD ^=  (1 << clockwire);
		_delay_ms(100);
	}
	
	PORTD &= ~ (1 << datawire); 
	PORTD &= ~ (1 << clockwire);
	PORTD |= (1 << latchwire);

	
		
	while (1){   
	
	
		
		
		
		
	/*	
	PORTD |= (1 << digit_act1);  
	animation();	 
	PORTD &= ~ (1 << digit_act1);  
	PORTD |= (1 << digit_act2); 
	animation();
	PORTD &= ~ (1 << digit_act2);  
	PORTD |= (1 << digit_act3);
	animation(); 
	PORTD &= ~ (1 << digit_act3); 
	PORTD |= (1 << digit_act4); 
	animation(); 
	PORTD &= ~ (1 << digit_act4); 
	*/	 
	
	}
	 


}

void num_1_tog(void){
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_6);
}

void num_1_on(void){ 
	PORTC &= ~ (1 << segment_3); 
	PORTC &= ~ (1 << segment_6);	  
} 

void num_2_on(void){
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3); 
	PORTC &= ~ (1 << segment_4);
	PORTB &= ~ (1 << segment_5); 
	PORTC &= ~ (1 << segment_7);
	
} 

void num_3_on(void){
	
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3);
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_6);
	PORTC &= ~ (1 << segment_7);
	
} 

void num_4_on(void){
	
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_3);
	PORTC &= ~ (1 << segment_6);
} 

void num_5_on(void){
	
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_6); 
	PORTC &= ~ (1 << segment_7);
} 

void num_6_on(void){
	
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_6);
	PORTC &= ~ (1 << segment_7); 
	PORTB &= ~ (1 << segment_5);
} 

void num_7_on(void){
	
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3);
	PORTC &= ~ (1 << segment_6);
	
} 

void num_8_on(void){
	
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3);
	PORTC &= ~ (1 << segment_4);
	PORTB &= ~ (1 << segment_5);
	PORTC &= ~ (1 << segment_7); 
	PORTC &= ~ (1 << segment_6);
} 

void num_9_on(void){
	
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3);
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_6);   
} 

void num_0_on(void){
	
	PORTC &= ~ (1 << segment_1);
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3);
	
	PORTB &= ~ (1 << segment_5);
	PORTC &= ~ (1 << segment_6); 
	PORTC &= ~ (1 << segment_7);
} 
 
//////////////////////////////////// 

void num_1_off(void){
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_6);
}

void num_2_off(void){ 
	
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_4);
	PORTB |= (1 << segment_5);
	PORTC |= (1 << segment_7);
	
}

void num_3_off(void){
	
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_6);
	PORTC |= (1 << segment_7);
	
}

void num_4_off(void){
	
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_6);
}

void num_5_off(void){
	
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_6);
	PORTC |= (1 << segment_7);
}

void num_6_off(void){
	
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_6);
	PORTC |= (1 << segment_7);
	PORTB |= (1 << segment_5);
}

void num_7_off(void){
	
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_6);
	
}

void num_8_off(void){
	
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_4);
	PORTB |= (1 << segment_5);
	PORTC |= (1 << segment_7);
	PORTC |= (1 << segment_6);
}

void num_9_off(void){
	
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_6);
}

void num_0_off(void){
	
	PORTC |= (1 << segment_1);
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_3);
	
	PORTB |= (1 << segment_5);
	PORTC |= (1 << segment_6);
	PORTC |= (1 << segment_7);
} 

void animation (void){
		int n = 10;
		int m = 100;
	
	PORTC &= ~ (1 << segment_1);
	_delay_ms(n);
	PORTC &= ~  (1 << segment_2);
	_delay_ms(n);
	PORTC &= ~ (1 << segment_3);
	_delay_ms(n);
	PORTC &= ~ (1 << segment_4);
	_delay_ms(n);
	PORTB &= ~  (1 << segment_5);
	_delay_ms(n);
	PORTC &= ~ (1 << segment_7);
	_delay_ms(n);
	PORTC &= ~ (1 << segment_6);
	_delay_ms(n);
	PORTC |= (1 << segment_1);
	_delay_ms(n);
	PORTC |= (1 << segment_2);
	_delay_ms(n);
	PORTC |= (1 << segment_3);
	_delay_ms(n);
	PORTC |= (1 << segment_4);
	_delay_ms(n);
	PORTB |= (1 << segment_5);
	_delay_ms(n);
	PORTC |= (1 << segment_7);
	_delay_ms(n);
	PORTC |= (1 << segment_6);
	_delay_ms(n);
	
	/////////////////////
	
	num_1_on();
	_delay_ms(m);
	num_1_off();
	
	num_2_on();
	_delay_ms(m);
	num_2_off();
	
	
	num_3_on();
	_delay_ms(m);
	num_3_off();
	
	
	num_4_on();
	_delay_ms(m);
	num_4_off();
	

	num_5_on();
	_delay_ms(m);
	num_5_off();
	
	
	num_6_on();
	_delay_ms(m);
	num_6_off();

	
	num_7_on();
	_delay_ms(m);
	num_7_off();
	
	
	num_8_on();
	_delay_ms(m);
	num_8_off();

	
	num_9_on();
	_delay_ms(m);
	num_9_off();
	
	
	num_0_on();
	_delay_ms(m);
	num_0_off();
	
}