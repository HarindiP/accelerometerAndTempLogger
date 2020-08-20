/*Library for accelerometer from the MMA8452Q Sparkfun website
 * 
 * This sketch uses the Sparkfun_MMA8452Q library to initialise the accelerometer and stream
 * calculated x y z , accleration values from it (in g units) and reads the temperature sensor
 * 
 * 
 * Hardware Hookup :
 * 
 * Uno Wifi ---------------- MMA8452Q Board (Tilt Sensor)
 *   3.3V  ---------------- VCC
 *   GND   ---------------- GND 
 *   SDA   --\/ 330 Ohm \/-- SDA 
 *   SCL   --\/ 330 Ohm \/-- SCL 
 * 
 * Uno Wifi ---------------- Temperature Sensor
 *   GND  ---------------- 1
 *   A0   ---------------- 2 
 *   5V   ---------------- 3
 * \
 * 
 * The MMA8452Q is a 3.3V max sensor, so you'll need to do some
 * level-shifting between the Arduino and the breakout. Series 
 * resistors on the SDA and SCL lines should do the trick.
 * 
 * 
 * Connect the following OpenLog to Arduino: 
 * RXI of OpenLog to TX on Arduino
 * VCC to 5V
 * GND to GND
 * 
 * 
 */

#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;        //The variable we will use to store temperature in degrees. 

MMA8452Q accel;                   // create instance of the MMA8452 class
int x=0;                          // create iterator that loops number of measurements



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Example print to OpenLog");
  Serial.println("Anything printed to COM port gets logged!");
  Serial.println("This ones an intergrated model with the uno");

  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  
}

void loop() {

    if (x <20) {
      if (accel.available()) {      // Wait for new data from accelerometer
        
      // Acceleration of x, y, and z directions in g units

      Serial.print("X  |  Y  |  Z  : ");
      Serial.print("\t");
      Serial.print(accel.getCalculatedX(), 3);
      Serial.print("\t");
      Serial.print(accel.getCalculatedY(), 3);
      Serial.print("\t");
      Serial.print(accel.getCalculatedZ(), 3);
      Serial.println();

      sensorInput = analogRead(A0);    //read the analog sensor and store it
      temp = (double)sensorInput / 1024;       //find percentage of input reading
      temp = temp * 5;                 //multiply by 5V to get voltage
      temp = temp - 0.5;               //Subtract the offset 
      temp = temp * 100;               //Convert to degrees 
      
      Serial.print("Current Temperature: ");
      Serial.println(temp);
      
      delay(200);
      
    x++;
    
    }  
  }  

  

  
  

}
