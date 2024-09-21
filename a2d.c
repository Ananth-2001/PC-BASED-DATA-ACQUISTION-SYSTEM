#define CLRBIT(a,b) (a=a&(~(1<<b)))
typedef float f32;
typedef unsigned char u8;
typedef unsigned int u32;
#define CS 7
void delay_ms(int );
u8 SPIO(u8 );
f32 a2d_read(u8 channel_no)
{
     u8 hbyte,lbyte;
	 u32 adc_val=0;
	 IOCLR0=1<<CS;
	 SPIO(0x06);
     delay_ms(10);
	 hbyte=SPIO(channel_no<<6);
	 delay_ms(10);
	 lbyte=SPIO(0x00);
	 IOSET0=1<<CS;
	 adc_val=((hbyte&0x0f)<<8)|lbyte;

	 return ((adc_val*3.3)/4096);
}

