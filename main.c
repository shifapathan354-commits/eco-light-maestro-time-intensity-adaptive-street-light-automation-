#include <LPC21xx.h>

void lcd_init(void);
void interrupt_init(void);
void lcd_cmd(unsigned char);
void lcd_string(char *);
void lcd_data(unsigned char);
void delay_ms(unsigned int);

void keypad_init(void);
char keypad_scan(void);

void rtc_init(void);
void rtc_display(void);

void adc_init(void);
unsigned int adc_read(void);

void led_init(void);
void led_on(void);
void led_off(void);

char key;

unsigned char hour1,hour2;
unsigned char min1,min2;
unsigned char sec1,sec2;

unsigned int ldr;

void wait_release(void)
{
    while(keypad_scan() != 0);
}

void lcd_backspace(void)
{
    lcd_cmd(0x10);

    lcd_data(' ');

    lcd_cmd(0x10);
}

void rtc_edit(void)
{
    // ENTER HOUR

    lcd_cmd(0x01);

    lcd_string("ENTER HOUR:");

    lcd_cmd(0xC0);

    while(1)
    {
        hour1 = keypad_scan();

        if(hour1 == '#')
        {
            lcd_backspace();
        }

        else if(hour1 != 0)
        {
            lcd_data(hour1);

            wait_release();

            break;
        }
    }

    while(1)
    {
        hour2 = keypad_scan();

        if(hour2 == '#')
        {
            lcd_backspace();
        }

        else if(hour2 != 0)
        {
            lcd_data(hour2);

            wait_release();

            break;
        }
    }

    HOUR = ((hour1-48)*10) + (hour2-48);

    delay_ms(100);

    // ENTER MINUTE

    lcd_cmd(0x01);

    lcd_string("ENTER MIN:");

    lcd_cmd(0xC0);

    while(1)
    {
        min1 = keypad_scan();

        if(min1 == '#')
        {
            lcd_backspace();
        }

        else if(min1 != 0)
        {
            lcd_data(min1);

            wait_release();

            break;
        }
    }

    while(1)
    {
        min2 = keypad_scan();

        if(min2 == '#')
        {
            lcd_backspace();
        }

        else if(min2 != 0)
        {
            lcd_data(min2);

            wait_release();

            break;
        }
    }

    MIN = ((min1-48)*10) + (min2-48);

    delay_ms(30);

    // ENTER SECOND

    lcd_cmd(0x01);

    lcd_string("ENTER SEC:");

    lcd_cmd(0xC0);

    while(1)
    {
        sec1 = keypad_scan();

        if(sec1 == '#')
        {
            lcd_backspace();
        }

        else if(sec1 != 0)
        {
            lcd_data(sec1);

            wait_release();

            break;
        }
    }

    while(1)
    {
        sec2 = keypad_scan();

        if(sec2 == '#')
        {
            lcd_backspace();
        }

        else if(sec2 != 0)
        {
            lcd_data(sec2);

            wait_release();

            break;
        }
    }

    SEC = ((sec1-48)*10) + (sec2-48);

    lcd_cmd(0x01);

    lcd_string("RTC UPDATED");

    delay_ms(30);

    lcd_cmd(0x01);
}

void rtc_menu(void)
{
    lcd_cmd(0x01);

    lcd_cmd(0x80);

    lcd_string("1.RTC EDIT");

    lcd_cmd(0xC0);

    lcd_string("#.EXIT");

    while(1)
    {
        key = keypad_scan();

        if(key == '1')
        {
            wait_release();

            rtc_edit();

            break;
        }

        else if(key == '#')
        {
            wait_release();

            lcd_cmd(0x01);

            lcd_string("EXIT");

            delay_ms(30);

            lcd_cmd(0x01);

            break;
        }
    }
}

int main()
{
    lcd_init();

    keypad_init();

    rtc_init();

    adc_init();

    led_init();
	  led_on();

    lcd_cmd(0x80);

    lcd_string("STREET LIGHT");

    delay_ms(30);

    lcd_cmd(0x01);

    while(1)
    {
        key = keypad_scan();

        // OPEN RTC MENU

        if(key == '*')
        {
            wait_release();

            rtc_menu();
        }

        // DISPLAY RTC

        rtc_display();

        // READ LDR VALUE

        ldr = adc_read();

        // NIGHT CONDITION
        // 6 PM TO 6 AM

        if((HOUR >= 18) || (HOUR < 6))
        {
            // DARK CONDITION

            if(ldr < 1024)
            {
                led_on();
            }
            else
            {
                led_off();
            }
        }
        else
        {
            led_off();
        }

        delay_ms(1);
    }
}