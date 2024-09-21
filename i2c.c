#define SCL	0x10
#define SDA 0x40
#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN 6
#define CCLK 60000000
#define PCLCK CCLK/4
#define i2c_speed 100000
#define SPEED ((PCLCK/i2c_speed)/2)
typedef unsigned char u8;
void i2c_init(void)
{
   PINSEL0|=SCL|SDA;	  
   I2SCLL=75;
   I2SCLH=75;
   I2CONSET=1<<I2EN;
}
void i2c_start(void)
{
	I2CONSET=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;

}
void i2c_restart(void)
{
	I2CONSET=1<<STA;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}
void i2c_write(u8 slave_addr)
{
   I2DAT=slave_addr;
   I2CONCLR=1<<SI;
   while(((I2CONSET>>SI)&1)==0);
}
void i2c_stop()
{
   I2CONSET=1<<STO;
   I2CONCLR=1<<SI;
}
u8 i2c_nack()
{
   I2CONCLR=1<<SI;
   while(((I2CONSET>>SI)&1)==0);
   return I2DAT;
}
u8 i2c_masterack(void)
{	
    I2CONSET = 0x04; //Assert Ack
    I2CONCLR = 1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR = 0x04; //Clear Assert Ack
	return I2DAT;
}


