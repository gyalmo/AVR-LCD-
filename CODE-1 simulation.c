#include <avr/io.h>                                                      
#include <util/delay.h>                                                  
#define LCD_Data_Dir DDRB                                               
#define LCD_Command_Dir DDRC                                           
#define LCD_Data_Port PORTB                                          
#define LCD_Command_Port PORTC                                         
#define RS PC0     
#define RW PC1   
#define EN PC2   
void LCD_Command  (unsigned char cmnd)

{ 
    LCD_Data_Port= cmnd;
    LCD_Command_Port &= ~(1<<RS);           
    LCD_Command_Port &= ~(1<<RW);           
    LCD_Command_Port |= (1<<EN);             
    _delay_us(1);
    LCD_Command_Port &= ~(1<<EN);
    _delay_ms(3);
}
 void LCD_Char (unsigned char char_data)  
{
    LCD_Data_Port= char_data;
    LCD_Command_Port |= (1<<RS);              
    LCD_Command_Port &= ~(1<<RW);       
    LCD_Command_Port |= (1<<EN);             
    _delay_us(1);
    LCD_Command_Port &= ~(1<<EN);
    _delay_ms(1);
}
 void LCD_String (char *str)  
{
    int i;
    for(i=0;str[i]!=0;i++)      
    {
        LCD_Char (str[i]);
    }
}
 void LCD_String_xy (char row, char pos, char *str)                                                                                      
              
{
    if (row == 0 && pos<16)
    {
        LCD_Command((pos & 0x0F)|0x80);
    }
    else if (row == 1 && pos<16)
    {
            
LCD_Command((pos & 0x0F)|0xC0);      
    }
     LCD_String(str);        
}
 int main()
{            
    LCD_Command_Dir = 0xFF; 
    LCD_Data_Dir = 0xFF;    
    _delay_ms(20);          
    LCD_Command (0x38);     
    LCD_Command (0x0C);     
    LCD_Command (0x06);     
    LCD_Command (0x01);     
    LCD_String_xy(0,3,"WELCOME");  
    LCD_Command(0xC0);        
    LCD_String_xy(1,5,"TO LPU");
    return 0;
}
