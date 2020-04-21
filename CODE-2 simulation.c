#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#define Data_direction DDRD
#define Data_Port PORTB
#define Cmd_Port PORTC    
#define rs PORTCbits.RC0
#define rw PORTCbits.RC1
#define en PORTCbits.RC2
 
void LCD_Cmd(unsigned char val)
{ 
Data_Port= val;
Cmd_Port  &= ~(1<<RS);
Cmd_Port  &= ~(1<<RW);        
Cmd_Port |= (1<<EN);    
_delay_us(1);    
Cmd_Port  &= ~(1<<EN);    
_delay_ms(2);
}

void LCD_Write(unsigned char ch)                                  // to display on LCD
{ 
Data_Port= ch;
Cmd_Port  |= ~(1<<RS);
Cmd_Port  &= ~(1<<RW);        
Cmd_Port |= (1<<EN);    
_delay_us(1);    
Cmd_Port  &= ~(1<<EN);    
_delay_ms(2);
}

void LCD_String(char *str)
{ 
  int i;    
  for(i=0;str[i]!=0;i++)    
{        
   LCD_Char (str[i]);    
}
}
void LCD_String_position(char row, char pos, char *str) 
 {    
if (row == 0 && pos<16)
{
 LCD_Cmd((pos & 0x0F)|0x80)
}    
else if (row == 1 && pos<16)    
{    
 LCD_Cmd((pos & 0x0F)|0xC0);  
}    
LCD_String(str);
}


int main(void)
{
  DDRD =0XFF;
 _delay_ms(10);
  LCD_Cmd(0x80);
  LCD_Cmd(0x38);                                              // Initialization of 16X2 LCD in 8bit 
  LCD_Cmd(0x0F);
  LCD_Cmd(0x01);
  LCD_String_position(0,4,"Embedded");  
  LCD_Command(0xC0);        
  LCD_String_position(1,6,"System");   

Return 0;
}
