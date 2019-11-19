/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN_1 = 8;
const int LOADCELL_SCK_PIN_1  = 9;
const int LOADCELL_DOUT_PIN_2 = 6;
const int LOADCELL_SCK_PIN_2  = 7;

HX711 scale;
HX711 scal2;

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN_1 , LOADCELL_SCK_PIN_1 );
  scal2.begin(LOADCELL_DOUT_PIN_2 , LOADCELL_SCK_PIN_2 );
 
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println((scale.read() + scal2.read())/2);			// print a raw reading from the ADC 
  
  Serial.print("read average: \t\t");
  Serial.println((scale.read_average(20)+scal2.read_average(20))/2);  	// print the average of 20 readings from the ADC

  
  Serial.print("get value: \t\t");
  Serial.println((scale.get_value(5)+scal2.get_value(5))/2);		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println((scale.get_units(5)+scal2.get_units(5))/2, 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println((scale.read_average(20)+scal2.read_average(20))/2);       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println((scale.get_value(5)+scal2.get_value(5))/2);		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println((scale.get_units(5)+scal2.get_units(5))/2, 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale
  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print((scale.get_units()+scal2.get_units())/2, 1);
  Serial.print("\t| average:\t");
  Serial.println((scale.get_units(10)+scal2.get_units(10))/2, 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
