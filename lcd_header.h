#include<LPC21XX.H>
#include "timer.h"
#define LCD_D 0xf<<20
#define RS 1<<17//P1.17
#define RW 1<<18//P1.18
#define E 1<<19//P1.19
void lcd_init(void);
void lcd_command(char);
void lcd_data(char);
					 
void lcd_init(void)
{
     IODIR1=LCD_D|RS|E|RW;
	  IOCLR1=RW;
     lcd_command(0x01);
	 lcd_command(0x02);	 
	 lcd_command(0x0C);
	 lcd_command(0x28);
	 lcd_command(0x80);
}
void lcd_command(char CMD)
{
    IOCLR1=LCD_D;
    IOSET1=(CMD&0XF0)<<16;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
	 IOCLR1=LCD_D;
   IOSET1=(CMD&0X0F)<<20;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void lcd_data(char DATA)
{
    IOCLR1=LCD_D;
    IOSET1=(DATA&0XF0)<<16;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
	
	 IOCLR1=LCD_D;
  IOSET1=(DATA&0X0F)<<20;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void lcd_string(char * p)
{
	while(*p)
	{
		lcd_data(*p++);
	}
}
void lcd_int(int num)
{
   signed char i=0;
   char arr[20];
   if(num==0)
   lcd_data('0');
   else
   {
     if(num<0)
	 {
		 lcd_data('-');
     	 num=-num;
	 }
    while(num!=0)
    {
       arr[i++]=num%10;
	   num=num/10;
    }
    for(--i;i>=0;i--)
    lcd_data(arr[i]+48);
  }
}
void lcd_float(float f)
{
   int temp;
   temp=f;
   lcd_int(temp);
   lcd_data('.');
   temp=(f-temp)*1000;
   lcd_int(temp);
}

