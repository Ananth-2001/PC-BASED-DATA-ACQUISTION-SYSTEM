#define MODE0 0x00
#define MODE1 0x08
#define MODE2 0x10
#define MODE3 0x18
#define MSTR  5
#define LSBF  6
#define SPIE  7
#define SPEED1  15000000/100
#define CS 	 7
#define SPIF 7
#define READ(a,b)  ((a>>b)&1)
typedef unsigned char u8;
SPI_INIT()
{
   PINSEL0|=0x00001500;
   S0SPCCR=SPEED1;
   S0SPCR=((1<<MSTR)|MODE3);
   IODIR0|=1<<7;
}
u8 SPIO(u8 data)
{
   u8 stat;
   stat = S0SPSR;
  S0SPDR=data;
  while(READ(S0SPSR,SPIF)==0);
  return S0SPDR;
}
