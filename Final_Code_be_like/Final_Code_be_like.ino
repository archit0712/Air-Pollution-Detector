#include <MQ135.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12 ,11 ,5 ,4 ,3 ,2 );

int sensor =0;
String quality ="";

#define beeper 8
#define led 9

#define anInput     A0                        //analog feed from MQ135

#define co2Zero     55               //calibrated CO2 0 level
                        


void setup() {
 Serial.begin(9600);
 pinMode(beeper,OUTPUT);
 pinMode(led,OUTPUT);
 pinMode(anInput,INPUT);
 lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Air Poll Dect.");
  lcd.setCursor(0,1);
  lcd.print("Warming sensor");
  delay(10000);

  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,1);
  lcd.print("               ");



 

}

void loop() {

 
 int co2now[10];                               //int array for co2 readings
int co2raw = 0;                               //int for raw value of co2
int co2comp = 0;                              //int for compensated co2 
int co2ppm = 0;                               //int for calculated ppm
int zzz = 0;                                  //int for averaging





  for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(A0);
    delay(200);
  }

for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                            //divide samples by 10    //C02raw is raw value of pollutants
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,100,5000);      //map value for atmospheric levels
Serial.println(co2ppm);
 delay(1000);
 lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  

 lcd.setCursor(0,0);
 lcd.print(co2ppm);
  
 
 if(co2ppm<200){
  
    quality = "Good";
  }
  else if (co2ppm>=200 && co2ppm<400){
    quality = "Very Unhealthy!";
     
   
  }
  else if (co2ppm>=400 && co2ppm<575){
    quality = "!!Wear Mask!!";
  }
  else if(co2ppm>=575 && co2ppm<750){
    quality="!!!Hazardous!!!";
     digitalWrite(beeper,HIGH);
     digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(beeper,LOW);
    digitalWrite(led,LOW);
  
  }
  else {
    quality="Stay in cover";
   digitalWrite(beeper,HIGH);
    delay(1000);
    digitalWrite(led,HIGH);
  }
  lcd.setCursor(0,1);
  lcd.print(quality);
}
