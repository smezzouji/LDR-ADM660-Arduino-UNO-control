/*Sulaimane Mezzouji
Diseño de una plataforma de medida de luz y temperatura basada en Arduino
Instrumentación Electrónica-14/15 UGR */
//Bibliotecas
#include <Wire.h> 
#include <DS1621.h>

int valorLDR = 0; 

byte addr = (0x90 >> 1) | 0;  // reemplaza  el 0 por uno de los valores puestos en los pines A2, A1 y A0
DS1621 sensor=DS1621(addr);

void setup()
{
  sensor.startConversion(false);                       
  sensor.setConfig(DS1621::POL | DS1621::ONE_SHOT);                    
  sensor.setThresh(DS1621::ACCESS_TH, 27);                     
  sensor.setThresh(DS1621::ACCESS_TL, 24);          
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
  delay(5);
  Serial.println("DS1621 & LDR");

}

void loop()
{
 for (int i=0; i<2; i++) {
   valorLDR = analogRead(A0);
  float voltage = valorLDR * (5.0 / 900.0);
  Serial.print("Luz:");
  Serial.println(voltage);
 if (voltage < 0.7) {
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(3, LOW);
  } 
  delay(1000);
 }
  int tC, tFrac;
  
  tC = sensor.getHrTemp();       
  
  if (tC < 0) {
    tC = -tC;                                  
    Serial.print("-");                         
  }
  
  tFrac = tC % 100;                             
  tC /= 100;                                    
  
  Serial.print("Temp:");
  Serial.print(tC);
  Serial.print(".");
  if (tFrac < 10)
    Serial.print("0");
  Serial.println(tFrac);
  if (tC >= 26) {
    digitalWrite(4, HIGH);
  }
  else {
    digitalWrite(4, LOW);
  } 
}
