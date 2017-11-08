#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

volatile float time = 0;
volatile float time_last = 0;
volatile int rpm_array[5] = {0,0,0,0,0};

void setup()
{
  //Digital Pin 2 Set As An Interrupt
 attachInterrupt(0, fan_interrupt, FALLING);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  analogWrite(10,255);
  lcd.print("Current RPM:");
    Serial.begin(9600);
}

//Main Loop To Calculate RPM and Update LCD Display
void loop()
{
  int rpm = 0;
  
  while(1){    

     //Slow Down The LCD Display Updates
  //delay(400);
  
  //Clear The Bottom Row
  lcd.setCursor(0, 1);
  lcd.print("                ");   
  
  //Update The Rpm Count
 
  lcd.setCursor(0, 1);
  lcd.print(rpm); 
  Serial.println(rpm);  

  ////lcd.setCursor(4, 1);
  ////lcd.print(time);   

  //Update The RPM
    //5 Sample Moving Average To Smooth Out The Data
      rpm_array[4] = 60*(1000000/(time));    
    //Last 5 Average RPM Counts Eqauls....
      rpm = (rpm_array[4]);
  
 
 }
}

//Capture The IR Break-Beam Interrupt
void fan_interrupt()
{
   time = (micros() - time_last); 
   time_last = micros();
}
