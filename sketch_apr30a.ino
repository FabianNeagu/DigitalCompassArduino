#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Arduino.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
int N=2;
int NE=3;
int E=4;
int SEE=5;
int S=6;
int SV=7;
int V=8;
int NV=9;

const int latchPin = 11;
const int clockPin = A0;
const int dataPin = 10;
const int caracter1 = 12;
const int caracter2 = 13;

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
void stopLEDS(void)
{
  digitalWrite(N,LOW);
  digitalWrite(NE,LOW);
  digitalWrite(E,LOW);
  digitalWrite(SEE,LOW);
  digitalWrite(S,LOW);
  digitalWrite(SV,LOW);
  digitalWrite(V,LOW);
  digitalWrite(NV,LOW);
  delay(5);
}

void setup(void)
{ 
  pinMode(N,OUTPUT);
  pinMode(NE,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(SEE,OUTPUT);
  pinMode(S,OUTPUT);
  pinMode(SV,OUTPUT);
  pinMode(V,OUTPUT);
  pinMode(NV,OUTPUT);
  
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  if(!mag.begin())
  {
    // Aparitie problema magnetometru 
    Serial.println("Eroare Magentometru");
    while(1);
  }
  
  // Afisare informatii magnetometru 
  displaySensorDetails();
  TIMSK1 = (1 << TOIE1);
  TCCR1A = 0;        
  TCCR1B = 0;
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(caracter1, OUTPUT);
  pinMode(caracter2, OUTPUT);
  digitalWrite(caracter1,HIGH);
  digitalWrite(caracter2,HIGH);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
  TCCR1B |= (1 << CS12);
  
}

void loop()
{
 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  // Afisare axe 
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  int heading=atan2(event.magnetic.y, event.magnetic.x)/0.0174532925; //Formula de calcul  in grade ( nu radiani )
  //Convertire in intervalul de grade 0 - 360
  if(heading < 0) 
    heading+=360;

  heading = 360-heading;
  Serial.println(heading); //Afisare in consola gradele


  //Aprindere LED corespunzator + Afisare directie pe LCD
  if (heading > 338 || heading < 22)

  {

   Serial.println("NORTH");
   stopLEDS();
   digitalWrite(N,HIGH);
   
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1110110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0000000));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 22 && heading < 68)

  {

    Serial.println("NORTH-EAST");
     stopLEDS();
    digitalWrite(NE,HIGH);

    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1110110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1111001));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);
  }
   if (heading > 68 && heading < 113)

  {

    Serial.println("EAST");
     stopLEDS();
    digitalWrite(E,HIGH);
    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1111001));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0000000));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 113 && heading < 158)

  {

    Serial.println("SOUTH-EAST");
       stopLEDS();
    digitalWrite(SEE,HIGH);
    
    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1101101));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1111001));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 158 && heading < 203)

  {

    Serial.println("SOUTH");
   stopLEDS();
    digitalWrite(S,HIGH);
    

   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1101101));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0000000));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 203 && heading < 248)

  {

    Serial.println("SOTUH-WEST");
   stopLEDS();
    digitalWrite(SV,HIGH);

    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1101101));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0111110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 248 && heading < 293)

  {

    Serial.println("WEST");
   stopLEDS();
    digitalWrite(V,HIGH);

    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0111110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0000000));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);

  }

  if (heading > 293 && heading < 338)

  {

    Serial.println("NORTH-WEST");
   stopLEDS();
    digitalWrite(NV,HIGH);

   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B1110110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter1,LOW);
   delay(5);
   digitalWrite(caracter1,HIGH);
  
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, (B0111110));
   digitalWrite(latchPin, HIGH);
   digitalWrite(caracter2,LOW);
   delay(5);
   digitalWrite(caracter2,HIGH);
  }

}
ISR(TIMER1_OVF_vect) {
}
