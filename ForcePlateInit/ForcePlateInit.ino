//Force Plate sensor code
#include <HX711.h>

//Subject to change
const int LOADCELL_DOUT_PIN = 2; 
const int LOADCELL_SCK_PIN = 3; 

const int calVal = 0; //Get this value from testing with known weights

double scale_1Val;
double scale_2Val;
double gravity = 9.81;
double mass;

HX711 scale1;
HX711 scale2;

void setup() {
  /*
## How to calibrate your load cell
1. Call `set_scale()` with no parameter.
2. Call `tare()` with no parameter.
3. Place a known weight on the scale and call `get_units(10)`.
4. Divide the result in step 3 to your known weight. You should
   get about the parameter you need to pass to `set_scale()`.
5. Adjust the parameter in step 4 until you get an accurate reading.
THIS PROCESS WILL ONLY BE DONE ONCE IN A DIFFERENT PROGRAM
*/
  scale1.set_scale(calVal);



 scale1.tare(); //This sets the scales reading to 0 at the start of the program
}
double scale_1Val;
double scale_2Val;
void loop() {
  // put your main code here, to run repeatedly:
 scale_1Val = scale1.get_units(5);
 scale_2Val = scale2.get_units(5);

 mass = (scale_1Val + scale_2Val)/2;

 force = mass*gravity;
 
}
