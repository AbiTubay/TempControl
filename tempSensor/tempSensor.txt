/**
 * Read temperature sensor and print out temperature
 * Abigail Tubay 2018
 */
#include <math.h>

//data variables
int a;
float t;                                      //temperature
int B=3975;                                   //B value of the thermistor
float r;
int pinTempSensor = 1;                        //Grove temperature sensor

/**
 * Set up serial monitor
 */
void setup(){
    Serial.begin(9600);
}

/**
 * read temperature sensor and calculate temperature
 * print out the value of the sensor, resistance
 * and the temperature in the serial monitor
 */
void loop(){
    a = analogRead(1);
    r = (float)(1023-a)*10000/a;              //get the resistance of the sensor;
    t = 1/(log(r/10000)/B+1/298.15)-273.15;   //convert to temperature via datasheet&nbsp;;
    delay(2000);                              //the sensor has an update rate of 2 seconds
    Serial.print(a);
    Serial.print(",");
    Serial.print(r);
    Serial.print(",");
    Serial.println(t);
}
