#include<avr/io.h>
#include<util/delay.h>

#define LCD_RS    PC0
#define LCD_En    
#define DAT4
#define DAT5 
#define DAT6
#define DAT7




#define CLEARDISPLAY 0x01
#define SETCURSOR 0x80

unsigned char temp, heart_beat;
unsigned int  t1;

unsigned char t2;

void hex2ascii(unsigned char value);
void counter0_int()interrupt 1
{
    TF=0;
}
void timer1_int()interrupt 3
{
TF1=0;
t1++;
}

void main()
{
    buzz=0;
    TMOD=0x26;
    TL0=0;
    TH0=0;
         TL1=0x48;
         TH1=0x48;
         IE=0x8A;
         TR0=1;
         TR1=1;

         LCD_init();
        LCD_str("Welcome  to");
        LCD_cmd(0xc0);
        LCD_str("My project");

        delay(65000);
        lcd_cmd(0x01);
        LCD_cmd(0x80);

        LCD_str("Health_monotoring_system");
        LCD_cmd(0xc0);
        LCD_str("Project");
        delay(65000);
        LCD_cmd(0x01);
        LCD_cmd(0x80);
        LCD_str("Temp Value:");

        LCD_cmd(0xc0);
        LCD_str("Heart Beat:");

        while(1)
        {
            rd = 1;
            wr  = 0;
            delay(100);
            wr  = 1;
            while(intr==1);
            delay(100);

            rd = 0;
            LCD_cmd(0x8c);
            temp = adc*2;
            hex2ascii(temp);

            intr = 1;
            if(t1>30000)
            {
                t2++;
                t1=0;
            }
            if(t2>7)
            {
                t2 = 0;
                LCD_cmd(0xcc);
                heart_beat = TL0*4;

                if(heart_beat>100 || heart_beat<60 || temp>100)
                {
                    buzz = 1;
                }

                else{
                    buzz = 0;
                }

                hex2ascii(heart_beat);
                TL0=0;
            }

        }

        LCD_str()



         
}

void hex2ascii(unsigned char value)
{
    unsigned char x, d1,d2, d3;
    x= value/10;
    d3=value%10;
    d2=x%10;
    d1=x/10;
    LCD_data(d1 + 0x30);
    LCD_data(d2 + 0x30);
    LCD_data(d3 + 0x30);
}

void LCD_init()
{
    LCD_cmd(0x38);
    LCD_cmd(0x01);
    LCD_cmd(0x80);
}

void delay(unsigned int i)
{
    unsigned int j;

    for(j = 0; j<i; j++);
}

void LCD_cmd(unnsigned char a)
{
    rs = 0;
    ldata = a;
    en = 1;
    delay(5);
    LCD_En = 0;
    delay(5);
}

void LCD_str(unsignedchar *str)
{
    while(*str)
    {
        LCD_data(*str++);
    }
}




