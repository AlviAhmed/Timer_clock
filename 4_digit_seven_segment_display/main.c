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

  
int main(void)
{	
	
	int n = 10;
	DDRD |= (1 << digit_act1); 
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
	PORTD |= (1 << digit_act1);  
	
	while (1){ 
		
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
	
	}
	 
	
	 
	

}

void num_1_on(void){ 
	PORTC &= ~ (1 << segment_3); 
	PORTC &= ~ (1 << segment_6);	  
} 

void num_2_on(void){
	PORTC &= ~ (1 << segment_2);
	PORTC &= ~ (1 << segment_3); 
	PORTC &= ~ (1 << segment_4);
	PORTC &= ~ (1 << segment_5); 
	PORTC &= ~ (1 << segment_7);
	
} 

void num_3_on