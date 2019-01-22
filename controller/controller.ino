  /**
   * Using LCD to display temperature values
   * Abigail Tubay
   */
  #include <LiquidCrystal.h>                     
  #include <math.h>
  
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
  
  //data variables
  int a;                                         
  float t;                                        //temperature
  int B = 3975;                                   //B value of the thermistor
  float r;                                        //resistor of thermistor
  int pinTempSensor = 1;                          //Grove temperature sensor
  int pin = 11;                                   //lamp
  float tTarget = 26.0;                           //target temperature
  float c = 1.0;                                  //sets 'LOW' and 'HIGH' temperatures

  /**
   * set up environments for lcd, temperature sensor, and lamp
   * print out 'Temperature:' on lcd
   */
  void setup(){
     lcd.begin(16, 2);               
     lcd.print("Temperature: "); 
     pinMode(pin, OUTPUT);
  }

  /**
   * read temperature sensor and calculate the temperature
   * print it out on the lcd
   * if the temperature reaches certain values turn lamp on or off
   */
  void loop(){
      a=analogRead(pinTempSensor);                //read Temperature sensor
      r=(float)(1023-a)*10000/a;                  //get the resistance of the sensor;
      t=1/(log(r/10000)/B+1/298.15)-273.15;       //convert to temperature via datasheet&nbsp;;

      //print temperature value on lcd with units
      lcd.setCursor(0,1);
      delay(1000);
      lcd.print(t);
      lcd.print("C");
  
      if(t<=tTarget-c){                           //turn on lamp if temperature <= 'LOW' temp
        digitalWrite(pin, HIGH);
      }else if(t>=tTarget+c){                     //turn off lamp if temp >= 'HIGH' temp
        digitalWrite(pin, LOW);
      }
  }
