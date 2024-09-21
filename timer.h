#include<LPC21xx.H>
void delay_ms(int sec)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<sec);
	T0TCR=0x03;
	T0TCR=0x00;
}
