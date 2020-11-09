/* 

 ----------------- ATtiny85 embedded program -----------------------------
 ------------------- Bucky : Buck convertor ------------------------------
 ---------- Designed and Developed by Aswin Sreekumar --------------------
  * Output PWM at IC PIN 5 : PB0
  * Pot Input at IC PIN 2 : PB3
  * Feedback Input at IC PIN 3 : PB4


*/

// Header file for AVR programming
#include<avr/io.h>

// Global variable for data input
int pot_input=0;        // To store potentiometer input ADC value

// Function to initialise registers
void initialise()
{
  DDRB=0x01;                                // Setting input-output ports

  TCCR0A|=(1<<WGM00)|(1<<WGM02);            // Set Waveform as Phase correct PWM
  TCCR0A|=(1<<COM0A0)|(1<<COM0A1);          // Set inverted compare match mode
  TCCR0B|=(1<<CS00)|(1<<CS01);              // Set frequency of PWM as 125 kHz using prescaler of 64
  
  ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);  // Enable ADC and set sampling rate at 125kHz
  ADMUX|=(1<<MUX1)|(1<<MUX0);               // Set ADC input channel as 3
}

void input_ADC()
{
  ADCSRA|=(1<<ADSC);            // Start ADC conversion
  while(!(ADCSRA&(1<<ADIF)));   // Wait for ADIF to go high, indicating completion
  pot_input=int(ADCL);          // Extracting lower 8 bits of data
  pot_input+=(int(ADCH)*256);   // Extracting higher 8 bits of data
}

int main()
{
  initialise();           // Initialising registers
  while(1)                // Infinite loop
  {
    input_ADC();          // Read input from potentiometer using ADC
    OCR0A= pot_input/4;   // Assign input value to output compare match
  }
}

// END OF CODE
