#include<LPC21XX.H>
#include<string.h>
#include "lcd_header.h"
#define CS 7
#define SLA_ADDR 0x68
#include "i2c.c"
#include "RTC.c"
#include "a2d.c"
#include "SPI.c"
void delay_ms(int sec);
void RTC_WRITE_READ(void);
void temp_to_terminal(f32);
void time_to_termianl(int,int,int);
void uart_string(char *);
typedef unsigned char u8;
typedef float f32;
int main()
{
     RTC_WRITE_READ();
	 lcd_command(0x80);
	 lcd_string("PC based DA");
}
void RTC_WRITE_READ(void)
{
     u8 sec;
	 u8 min;
	 u8 hr;
     f32 ans=0;
     SPI_INIT();
     lcd_init();
	 i2c_init();
     PINSEL0|=0x05;
	 RTC_WRITE(SLA_ADDR,0x00,10);
	 delay_ms(2);
	 RTC_WRITE(SLA_ADDR,0x01,5);
	 delay_ms(2);
	 RTC_WRITE(SLA_ADDR,0x02,1);
	 delay_ms(2);
	 U0LCR=0x83;
	 U0DLL=97;
	 U0LCR=0x03;
	 IOPIN0|=1<<CS;
	 while(1)
	 {
	       lcd_command(0xC0);
	       lcd_string("TEMPERATURE:");
	       sec=RTC_READ(SLA_ADDR,0x00);
	       sec=((sec/16)*10)+(sec%16);
		   min=RTC_READ(SLA_ADDR,0x01);
	       min=((min/16)*10)+(min%16);
		   hr=RTC_READ(SLA_ADDR,0x02);
	       hr=((hr/16)*10)+(hr%16);
		   time_to_termianl( sec, hr,min);
		   lcd_command(0x01);
		   lcd_command(0x80);
		  
		   lcd_int(hr);
		   lcd_data(':');
		   lcd_int(min);
		   lcd_data(':');
		   lcd_int(sec);
	
		   lcd_command(0xC0);
	       lcd_string("TEMPERATURE:");
		  
	       ans=a2d_read(0) ;
           lcd_float(ans*100);
	       delay_ms(200);
		   temp_to_terminal(ans*100);
		}
}
void temp_to_terminal(f32 f)
{
    u8 inte=f;
    uart_string("time: ");
    
	U0THR=(inte/10)+48;
    while(((U0LSR>>5)&1)==0);
    U0THR=(inte%10)+48;
	while(((U0LSR>>5)&1)==0);
	U0THR='.';
	while(((U0LSR>>5)&1)==0);
	inte=(f-inte)*100;
	U0THR=(inte/10)+48;
    while(((U0LSR>>5)&1)==0);
    U0THR=(inte%10)+48;
	while(((U0LSR>>5)&1)==0);
	U0THR='\r';
	while(((U0LSR>>5)&1)==0);
	U0THR='\n';
	while(((U0LSR>>5)&1)==0);

}
void time_to_termianl(int sec,int hr,int min)
{
           uart_string("temperature: ");
	       U0THR=(hr/10)+48;
		   while(((U0LSR>>5)&1)==0);
		   U0THR=(hr%10)+48;
		   while(((U0LSR>>5)&1)==0);
		   U0THR=':';
		   while(((U0LSR>>5)&1)==0);
		   U0THR=(min/10)+48;
		   while(((U0LSR>>5)&1)==0);
		   U0THR=(min%10)+48;
		   while(((U0LSR>>5)&1)==0);
		   U0THR=':';
		   while(((U0LSR>>5)&1)==0);
		   U0THR=(sec/10)+48;
		   while(((U0LSR>>5)&1)==0); 
		   U0THR=(sec%10)+48;
		   while(((U0LSR>>5)&1)==0);
		   delay_ms(400); 
		   U0THR='\r';
		   while(((U0LSR>>5)&1)==0);
		   U0THR='\n';
		   while(((U0LSR>>5)&1)==0);
}
void uart_string(char *s)
{
     while(*s)
	 {
          U0THR=*s++;
		   while(((U0LSR>>5)&1)==0); 
     }
}








