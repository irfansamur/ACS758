#define VIN A0 // define the Arduino pin A0 as voltage input (V in)
const float VCC   = 5.0;// supply voltage 5V or 3.3V. If using PCB, set to 5V only.
const int model = 4;   // enter the model (see below)
float cutOffLimit = 1.00;// reading cutt off current. 1.00 is 1 Amper
float sensitivity[] ={
          40.0,// for ACS758LCB-050B
          60.0,// for ACS758LCB-050U
          20.0,// for ACS758LCB-100B
          40.0,// for ACS758LCB-100U
          13.3,// for ACS758KCB-150B
          16.7,// for ACS758KCB-150U
          10.0,// for ACS758ECB-200B
          20.0,// for ACS758ECB-200U     
         }; 
float quiescent_Output_voltage [] ={
          0.5,// for ACS758LCB-050B
          0.12,// for ACS758LCB-050U
          0.5,// for ACS758LCB-100B
          0.12,// for ACS758LCB-100U
          0.5,// for ACS758KCB-150B
          0.12,// for ACS758KCB-150U
          0.5,// for ACS758ECB-200B
          0.12,// for ACS758ECB-200U            
          };
const float FACTOR = sensitivity[model]/1000;// set sensitivity for selected model
const float QOV =   quiescent_Output_voltage [model] * VCC;// set quiescent Output voltage for selected model
float voltage;// internal variable for voltage
float cutOff = FACTOR/cutOffLimit;// convert current cut off to mV
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

unsigned long milis;
float volt;
float watt;
unsigned long enerji;

void setup() {
  Serial.begin(9600);// initialize serial monitor
 lcd.begin(16,2);
  lcd.clear();
}

void loop() {

  float voltage_raw =   (5.0 / 1023.0)* analogRead(VIN);
  voltage =  voltage_raw - QOV +0.00133 ;
  float current = voltage / FACTOR;                                                                                                                                               
  if(abs(voltage) > cutOff ){                                                                                                               
    Serial.print("I: ");
    Serial.print(current); 
    Serial.println("A");
    Serial.print("\t");
      
  lcd.clear();
  lcd.setCursor (0,0); 
  lcd.print(current);
  lcd.print("A");
  
}

  else{
  Serial.println("No Current");   
  }

volt = analogRead(A2)*0.1262;  //bir kat sayı tespit edilecek
watt = current*volt;
enerji=watt*milis/1000;

Serial.print("V: ");
Serial.print(volt);
Serial.print("\t");
  lcd.clear();
  lcd.setCursor (6,0); 
  lcd.print(volt);
  lcd.print("V");

Serial.print("W: ");
Serial.print(watt);
Serial.print("\t");
    lcd.clear();
  lcd.setCursor (0,1); 
  lcd.print(watt);
  lcd.print("W");
if(current>5){ 
zaman();
Serial.print("J: ");
Serial.print(enerji);

  lcd.setCursor (7,1); 
  lcd.print(enerji);
  lcd.print("J");
  }
} 

unsigned long zaman(){
 milis = millis();
  return milis;
}
