#include <LPC21xx.h>

void adc_init(void)
{
    // Select AD0.1 on P0.28

    PINSEL1 &= ~(3<<24);

    PINSEL1 |= (1<<24);

    // ADC configuration

    ADCR = (1<<1) |      // Select channel AD0.1
           (15<<8) |     // Clock divider
           (1<<21);      // ADC enable
}

unsigned int adc_read(void)
{
    unsigned int val;

    // Start conversion

    ADCR |= (1<<24);

    // Wait for conversion complete

    while((ADDR & 0x80000000) == 0);

    // Read ADC value

    val = (ADDR >> 6) & 0x3FF;

    return val;
}