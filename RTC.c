typedef unsigned char u8;
void RTC_WRITE(u8 slave_addr,u8 word_addr,u8 data)
{
    i2c_start();
	i2c_write(slave_addr<<1);
	i2c_write(word_addr);
	i2c_write(data);
	i2c_stop();
	delay_ms(10);
}
u8 RTC_READ(u8 slave_addr,u8 word_addr)
{
     u8 ch;
     i2c_start();
	 i2c_write(slave_addr<<1);
	 i2c_write(word_addr);
	 i2c_restart();
	 i2c_write((slave_addr<<1)|1);
	 ch=i2c_nack();
	 i2c_stop();
	 return ch;
}


