/* Colorsensor - By Koen van Vliet <8by8mail@gmail.com>
 * Use an RGB LED and an LDR in series with a regular
 * resistor to detect colors.
 * Version: 0.1
 * Date: 20 dec 2014
 * Error: -
 * Note: You might need to calibrate the values for your LDR and LED.
 */
#define SENS A0
#define LEDR A1
#define LEDG A2
#define LEDB A3

#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define CLEAR 4
#define BLACK 5

#define DELAY 6

#define THR 420
#define THG 450
#define THB 350
#define THD 150

void setup(){
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDG,HIGH);
  digitalWrite(LEDB,HIGH);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  Serial.begin(115200);
}


void loop(){
  static unsigned char det = NONE, last = NONE, patt = 0, count = 0, hi;
  unsigned long rr, gg, bb;
  unsigned int pr, pg, pb;
  
  /*
  digitalWrite(LEDR,LOW);
  delay(DELAY);
  rr = analogRead(SENS);
  digitalWrite(LEDR,HIGH);
  
  digitalWrite(LEDG,LOW);
  delay(DELAY);
  gg = analogRead(SENS);
  digitalWrite(LEDG,HIGH);
  
  digitalWrite(LEDB,LOW);
  delay(DELAY);
  bb = analogRead(SENS);
  digitalWrite(LEDB,HIGH);
  */
  
  // Test for RED color
  digitalWrite(LEDR,LOW);
  delay(DELAY);
  rr = analogRead(SENS);
  digitalWrite(LEDR,HIGH);
  // Test for GREEN color
  digitalWrite(LEDG,LOW);
  delay(DELAY);
  gg = analogRead(SENS);
  digitalWrite(LEDG,HIGH);
  // Test for BLUE color
  digitalWrite(LEDB,LOW);
  delay(DELAY);
  bb = analogRead(SENS);
  digitalWrite(LEDB,HIGH);
  
  pr = (rr * 1000) / THR;
  pg = (gg * 1000) / THG;
  pb = (bb * 1000) / THB;
    
  /*
  Serial.print("Red:");
  Serial.print(rr);
  Serial.print(" Green:");
  Serial.print(gg);
  Serial.print(" Blue:");
  Serial.print(bb);
  */
  Serial.print("R=");
  Serial.print(pr);
  Serial.print("% G=");
  Serial.print(pg);
  Serial.print("% B=");
  Serial.print(pb);
  Serial.print("% ");
  if(pr / 3 > (pg / 2) && pr / 3 > (pb / 2)){
    Serial.print("[RED]");
  }
  if(pg / 3 > (pr / 2) && pg / 7 > (pb / 6)){
    Serial.print("[GREEN]");
  }
  if(pb / 3 > (pr / 2) && pb / 13 > (pg / 12)){
    Serial.print("[BLUE]");
  }
  Serial.println();
}
