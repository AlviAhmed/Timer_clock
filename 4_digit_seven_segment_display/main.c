/*
 * 4_digit_seven_segment_display.c
 *
 * Created: 2016-04-28 8:40:28 PM
 * Author : Alvi
 */ 

#define F_CPU 16000000UL
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



#define digit_act1 PD0 //Active HIGH pin 1 
#define digit_act2 PD1 //Active HIGH pin 2
#define digit_act3 PD2 //Active HIGH pin 6
#define digit_act4 PD3 //Active HIGH pin 8 
#define dotI_act     //Active  HIGH pin 10  

#define dotE_act //Active HIGH  pin 1 
#define dotF_act //Active HIGH  pin 2 
#define dotG_act  PB1//ACtive HIGH pin 4
#define dotH_act //Active HIGH pin 6 
#define dotJ_act //Active HIGH pin 8 


#define dotE PD4 //Active LOW 
#define dotI //Active LOW pin 9   

#define datawire PD5 
#define latchwire PD6 
#define clockwire PD7
int count = 0; 
int num_alarm[][4] = { {0,0,1,1},{0,0,1,2},{1,0,3,3},{1,2,3,4},{0,0,0,0},{4,4,4,4},{2,0,2,0}};  
int num_time [][4] = {0,3,4,4};
int size_row = ((sizeof(num_time) / sizeof(int)) / 4) - 1;    
int entries_row = ((sizeof(num_time) / sizeof(int)) / 4) - 1;    
int size_col = 3;
int arb = 0; 
int arb2 = 0;
int rows = 0;
int cols = 0;
int entries_col = 3;
int time_count = 0; 
int isr_count = 0; 
int timsec = 0,tim1 = 0, tim2 = 0, tim3 = 0, tim4 = 0;
int blinker = 0;
 
int main(void)
{	
	
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
	DDRB |= (1 << dotG_act);  
	DDRC |= (1 << segment_7);  
	
	PORTC |= (1 << segment_7);
	PORTC |= (1 << segment_6);
	PORTB |= (1 << segment_5); 
	PORTC |= (1 << segment_4);
	PORTC |= (1 << segment_3);
	PORTC |= (1 << segment_2);
	PORTC |= (1 << segment_1);
	PORTB |= (1 << dotG_act);
	
	PORTD &= ~ (1 << digit_act1);
	PORTD &= ~ (1 << digit_act2); 
	PORTD &= ~ (1 << digit_act3); 
	PORTD &= ~ (1 << digit_act4); 
	

	
		TCCR1B |= (1 << WGM12); 
		TIMSK1 |= (1 << OCIE1A); 
		sei(); 
		OCR1A = 800; 
		TCCR1B |= (1 << CS11); // 8 prescaler  
		
	
		
		while(1){ //Apparently if no infinite loop the ISR doesn't work
				
				
			
		}	
			
}




ISR (TIMER1_COMPA_vect){ 

	blinker ++;
	if (blinker >= 1250){
		PORTB ^= (1 << dotG_act); 
		blinker = 0;
	} 
	
	multiplex_func(num_time);  
	
	
	
	/*num_time[0][3]  += tim1;
	num_time[0][2]  += tim2;
	num_time[0][1]  += tim3;
	num_time[0][0]  += tim4; */
	if (timsec > 59){
		timsec = 0; 
		num_time[0][3]++;
	}
	if (num_time[0][3] > 9){
		num_time[0][3] = 0;
		num_time[0][2]++;
	}
	if ( ( num_time[0][2] == 6) && ( num_time[0][3]  == 0) ) {
		num_time[0][2] = 0; 
		num_time[0][3] = 0;
		num_time[0][1] ++;
	}
	if (num_time[0][1] > 9){
		num_time[0][1] = 0;
		num_time[0][0]++;
	}
	if ( (num_time[0][0] == 2) && (num_time[0][1] == 4) && (num_time[0][2] == 0) && (num_time[0][3] == 0) ){
		num_time[0][3] = 0;
		num_time[0][2] = 0;
		num_time[0][1] = 0;
		num_time[0][0] = 0;
	} 

isr_count ++;


if (isr_count >= 1250){
	timsec++; 

	//num_time[0][3]++;
	isr_count = 0;
	
}
	
	/*
		PORTD ^= (1 << digit_act1);
		PORTD ^= (1 << digit_act2);
		PORTD ^= (1 << digit_act3);
		PORTD ^= (1 << digit_act4);
	num_1_tog(); 
	*/   
	  
	
	
} 


void multiplex_func( int number[][4]){
	
	if ( arb <= entries_row){ 
		if (arb2 <= entries_col){  
			//Determining whether or not to switch on the first digit
			if (  (arb2 == 0) ){
				PORTD |= (1 << digit_act1); } else {PORTD &= ~ (1 << digit_act1);}
			//Determining whether or not to switch on the first digit
			if (  (arb2 == 1) ){
				PORTD |= (1 << digit_act2); } else {PORTD &= ~ (1 << digit_act2);}
			//Determining whether or not to switch on the first digit
			if (  (arb2 == 2) ){
				PORTD |= (1 << digit_act3); } else {PORTD &= ~ (1 << digit_act3);}
			//Determining whether or not to switch on the first digit
			if (  (arb2 == 3) ){
				PORTD |= (1 << digit_act4); } else {PORTD &= ~ (1 << digit_act4);}
			
			switch (number[arb][arb2]){
				case 1: 
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off();	
					num_1_on();
					arb2++;
					break;
				case 2:
					 
					num_1_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_2_on();
					arb2++;
					break; 
				case 3:
					 
					num_2_off();
					num_1_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_3_on();
					arb2++;
					break;
				case 4:
					
					num_2_off();
					num_3_off();
					num_1_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_4_on(); 
					arb2++;
					break; 
				case 5:
					 
					num_2_off();
					num_3_off();
					num_4_off();
					num_1_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_5_on();
					arb2++;
					break;
				case 6:
					 
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_1_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_6_on();
					arb2++;
					break;
				case 7:
					
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_1_off();
					num_8_off();
					num_9_off();
					num_0_off(); 
					num_7_on(); 
					arb2++;
					break;
				case 8:
					 
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_1_off();
					num_9_off();
					num_0_off(); 
					num_8_on();
					arb2++;
					break; 
				case 9:
					
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_1_off();
					num_0_off(); 
					num_9_on(); 
					arb2++;
					break;
				case 0:
					 
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off();
					num_1_off(); 
					num_0_on();
					arb2++;
					break;
				default:  
					num_0_off(); 
					num_1_off(); 
					num_2_off();
					num_3_off();
					num_4_off();
					num_5_off();
					num_6_off();
					num_7_off();
					num_8_off();
					num_9_off(); 
					break;
			} 
			if (arb2 > entries_col){
				arb2 = 0;
			}
			
		
	}
				
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


void num_1_tog(void){
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_6);
}

void num_2_tog(void){
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_4);
	PORTB ^= (1 << segment_5);
	PORTC ^= (1 << segment_7);
	
}

void num_3_tog(void){
	
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_4);
	PORTC ^= (1 << segment_6);
	PORTC ^= (1 << segment_7);
	
}

void num_4_tog(void){
	
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_4);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_6);
}

void num_5_tog(void){
	
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_4);
	PORTC ^= (1 << segment_6);
	PORTC ^= (1 << segment_7);
}

void num_6_tog(void){
	
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_4);
	PORTC ^= (1 << segment_6);
	PORTC ^= (1 << segment_7);
	PORTB ^= (1 << segment_5);
}

void num_7_tog(void){
	
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_6);
	
}

void num_8_tog(void){
	
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_4);
	PORTB ^= (1 << segment_5);
	PORTC ^= (1 << segment_7);
	PORTC ^= (1 << segment_6);
}

void num_9_tog(void){
	
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	PORTC ^= (1 << segment_4);
	PORTC ^= (1 << segment_6);
}

void num_0_tog(void){
	
	PORTC ^= (1 << segment_1);
	PORTC ^= (1 << segment_2);
	PORTC ^= (1 << segment_3);
	
	PORTB ^= (1 << segment_5);
	PORTC ^= (1 << segment_6);
	PORTC ^= (1 << segment_7);
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