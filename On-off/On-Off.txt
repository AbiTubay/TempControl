  /**
   * On-off.ino
   * On-Off control system
   * implementing the Arduino, voltage relay, temperature sensor
   * and the lcd display shield to create a thermostat
   * Abigail Tubay 2018
   */
   
  #include <LiquidCrystal.h>
  #include <math.h>
  
  LiquidCrystal lcd(8, 9, 4, 5, 6, 7);      // select the pins used on the LCD panel
  
  /**Data variables*/
  int lcd_key = 0;                  
  int lcd = 0;
  float a;                                  
  float t;                                  //temperature
  int B = 3975;                             //B value of the thermistor
  float r;                                  //resistance on the thermistor
  int pinTempSensor = 1;                    //Grove temperature sensor
  int pin = 11;                             //lamp
  int pinLcd = 0;                           //lcd
  float tTarget = 26.0;                     //target temperature
  float c = 1.0;                            //sets 'HIGH' and 'LOW' temp around target temp

  #define btnRIGHT  0
  #define btnUP     1
  #define btnDOWN   2
  #define btnLEFT   3
  #define btnSELECT 4
  #define btnNONE   5



  /** Read LCD buttons and select appropriate response */
  int read_LCD_buttons(){                   // read the buttons
      
      lcd = analogRead(pinLcd);             // read the value from the sensor 
        
      if (lcd < 50)   return btnRIGHT;  
      if (lcd < 250)  return btnUP; 
      if (lcd < 450)  return btnDOWN; 
      if (lcd < 650)  return btnLEFT; 
      if (lcd < 850)  return btnSELECT;  
      if (lcd > 1000) return btnNONE; 

  }


  /** 
   * Set bulb on or off
   * print target temperatures on the lcd
   */
  void bulb(float x, float y){
      //print target temperatures on the lcd
      lcd.setCursor(0,1);
      lcd.print("Tg: "); 
      lcd.print(tTarget);
      lcd.print("+-");
      lcd.print(c);
      
      if(t<=x-y){                            //turn on lamp if actual temp <= 'LOW' temp
         digitalWrite(pin, HIGH);
      }else if(t>=x+y){                      //turn lamp off if actual temp >= 'HIGH' temp
         digitalWrite(pin, LOW);
      }
  }

  /**
   * set up enviroments for lcd and lamp
   */
  void setup(){
     lcd.begin(16, 2);                        
     lcd.print("T: ");                
     pinMode(pin, OUTPUT);
  }


  /** 
   * reads the temperature sensor and computes the temperature in degree celsius
   * prints out the actual temperature
   * reads the lcd button outputs and set out an appropriate response
   */
  void loop(){
    
     a = analogRead(pinTempSensor);           //read temperature sensor
     r = (1023-a)*10000/a;                    //get the resistance of the sensor;
     t = 1/(log(r/10000)/B+1/298.15)-273.15;  //convert to temperature via datasheet&nbsp;;

     //print out actual temperature
     lcd.setCursor(3,0);
     lcd.print(t);
     lcd.print("C");

     lcd_key = read_LCD_buttons();            //read LCD buttons
     bulb(tTarget, c);                        //set out appropriate lamp response
     switch (lcd_key){               
         case btnRIGHT:{                      //increase HIGH temperature by 1
              c += 1;
              delay(500);
              bulb(tTarget, c);
              break;
         }  
         case btnLEFT:{                       //decrease LOW temperature by 1
              c -= 1;
              delay(500);
              bulb(tTarget, c);
              break;
         }    
         case btnUP:{                         //increase target temperature by 1
              tTarget += 1;
              delay(500);
              bulb(tTarget, c);
              break;
         }
         case btnDOWN:{                       //decrease target temperature by 1
              tTarget -= 1;
              delay(500);
              bulb(tTarget, c);
              break;
         }
         case btnSELECT:{                    //restart target temperature settings
              tTarget = 25.0;
              c = 1.0;
              bulb(tTarget, c);
              break;
         }
         case btnNONE:{
              break;
         }
     }
  }
