#include <LPC21xx.h>

#define LCDDATA 0x00FF0000

#define RS (1<<8)
#define EN (1<<9)

void delay_ms(unsigned int ms)
{
    unsigned int i,j;

    for(i=0;i<ms;i++)
    {
        for(j=0;j<6000;j++);
    }
}

void lcd_cmd(unsigned char cmd)
{
    IOCLR0 = LCDDATA;

    IOSET0 = (cmd<<16);

    IOCLR0 = RS;

    IOSET0 = EN;

    delay_ms(2);

    IOCLR0 = EN;
}

void lcd_data(unsigned char data)
{
    IOCLR0 = LCDDATA;

    IOSET0 = (data<<16);

    IOSET0 = RS;

    IOSET0 = EN;

    delay_ms(2);

    IOCLR0 = EN;
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);   
    }
}

void lcd_init(void)
{
    IODIR0 |= LCDDATA | RS | EN;

    delay_ms(20);

    lcd_cmd(0x38);

    lcd_cmd(0x0C);

    lcd_cmd(0x06);

    lcd_cmd(0x01);
}

void lcd_num(unsigned int num)
{
    char arr[5];

    int i=0;

    if(num==0)
    {
        lcd_data('0');

        return;
    }

    while(num)
    {
        arr[i++] = (num%10)+48;

        num = num/10;
    }

    while(i)
    {
        lcd_data(arr[--i]);
    }
	}