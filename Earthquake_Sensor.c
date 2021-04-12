#include <stdint.h>
#include <avr/io.h>
#include "libLCD/hd44780.h"
#include "IO_Macros.h"

void my_delay_ms(unsigned int delay);
void adc_init(void);
uint16_t read_adc(uint8_t channel);
uint16_t adc_val1, adc_val2;

int main() {
  DDRC &= ~(1<<PC4); // Set A4 & A5 as inputs.
  DDRC &= ~(1<<PC5);
  DDRD |= (1<<PD4); // Set Digital Pins 4 & 2 as output
  DDRD |= (1<<PD2);

  LCD_Setup();
  uint8_t line;
  for (line = 0; line < 2; line++)
	{
		LCD_GotoXY(0, line);
		if (line == 0)
		{
			LCD_PrintString("ECE 387 line: ");
			LCD_PrintInteger(LCD_GetY());
		}
		else 
		{
			LCD_PrintString("LCD[");
			LCD_PrintInteger(LCD_GetY());
			LCD_PrintString("] working!!!");
		}
	}
  my_delay_ms(1000);
  LCD_Clear();
  adc_init(); // Initialize the onboard ADC
  _delay_ms(15);

  while (1){
    adc_val1 = read_adc(4);	// Read the ADC value from sensor 1 in pin A4
    _delay_ms(15);
    adc_val2 = read_adc(5);	// Read the ADC value from sensor 2 in pin A5
    _delay_ms(15);

    if (adc_val1 > 512) {	// If ADC value from sensor 1 is > 512, turn LED in Digital Pin 4 on. Threshold can be changed between 0-1023.
      PORTD |= (1<<PD4);
      if (adc_val2 > 512) {
	PORTD |= (1<<PD2);
      }	
      LCD_Clear(); 		// Print sensor readings from ADC
      LCD_GotoXY(0,0);
      LCD_PrintString("Sensor 1: ");
      LCD_PrintInteger(adc_val1);
      LCD_GotoXY(0,1);
      LCD_PrintString("Sensor 2: ");
      LCD_PrintInteger(adc_val2);
      my_delay_ms(500);		// delay so values can be read on the screen. Can be safely changed
    }

    if (adc_val2 > 512) {	// If ADC value from sensor 1 is > 512, turn LED in Digital Pin 4 on. Threshold can be changed between 0-1023.
      PORTD |= (1<<PD2);
      if (adc_val1 > 512) {
	PORTD |= (1<<PD4);
      }	
      LCD_Clear(); 		// Print sensor readings from ADC
      LCD_GotoXY(0,0);
      LCD_PrintString("Sensor 1: ");
      LCD_PrintInteger(adc_val1);
      LCD_GotoXY(0,1);
      LCD_PrintString("Sensor 2: ");
      LCD_PrintInteger(adc_val2);
      my_delay_ms(500);		// delay so values can be read on the screen. Can be safely changed
    }

    else {
      PORTD &= ~(1<<PD4);    // Else turn led off
      PORTD &= ~(1<<PD2);
      LCD_Clear(); // Print sensor readings from ADC
      LCD_GotoXY(0,0);
      LCD_PrintString("Sensor 1: ");
      LCD_PrintInteger(adc_val1);
      LCD_GotoXY(0,1);
      LCD_PrintString("Sensor 2: ");
      LCD_PrintInteger(adc_val2);
      my_delay_ms(500); // Delay so values can be read. Can be safely changed
    }
  }
}
  
void adc_init(void) { // Helper methods allow for easier resetting of ADC
 
 ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    // Sets ADC clock to 125KHz (ADC only works within 50KHz-200KHz)
 ADMUX |= (1<<REFS0);                // Voltage reference from Vcc = 5V. Can set to external references, or internal 1.1V.
 ADCSRA |= (1<<ADEN);                // Enable ADC
 ADCSRA |= (1<<ADSC);                // Do a conversion to get things moving. 1st conversion takes longer due to startup time.
}
 

/*
 * channel = analog port to listen to. 
 * Values: 0-5 on an Atmega 328p (6 analog ports)
 */
uint16_t read_adc(uint8_t channel) {
 ADMUX &= 0xF0;                    // Clear the old channel
 ADMUX |= channel;                // Defines the new ADC channel to be read
 ADCSRA |= (1<<ADSC);                // Starts a new conversion
 while(ADCSRA & (1<<ADSC));            // Wait until the conversion is done (really short)
 return ADCW;                    // Returns the ADC value
}


void my_delay_ms(unsigned int delay) 
{
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	if (delay % 10) {
		_delay_ms(delay % 10);
	}
}
