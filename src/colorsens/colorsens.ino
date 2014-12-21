/* Colorsensor - By Koen van Vliet <8by8mail@gmail.com>
 * Use an RGB LED and an LDR in series with a regular
 * resistor to detect colors.
 * Version: 0.2
 * Date: 20 dec 2014
 * Error: Sometimes registers green - red transition as blue
 *
 * Note: Use calibrate.ino for calibrating your sensor.
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

#define DELAY 3

// Values from calibration
#define THR 420 // Red level
#define THG 450 // Green level
#define THB 350 // Blue level

#define PBK 400 // Black threshold
#define PCL 1600 // Clear threshold

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
  static unsigned char det = NONE, last = NONE, patt = 0, count = 0;
  unsigned long rr, gg, bb;
  unsigned int pr, pg, pb;
  do{
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
    
    // Calculate color values
    pr = (rr * 1000) / THR;
    pg = (gg * 1000) / THG;
    pb = (bb * 1000) / THB;
    
    // Determine which color was detected
    // Append one or zero depending on the color pattern
    if (pr + pg + pb < 800 ){
      if(det != BLACK){
        Serial.println("BLACK");
        det = BLACK;
        patt = 0;
        count = 0;
        Serial.println("Clear");
      }
    } else {
      if(pr / 3 > (pg / 2) && pr / 3 > (pb / 2)){
        if (det != RED){
          Serial.print("RED ");
          det = RED;
          if (last == GREEN){
            patt = (patt << 1) | 1;
            Serial.println("1");
          } else if (last == BLUE){
            patt = (patt << 1);
            Serial.println("0");
          }
          count ++;
        }
      } else if(pg / 3 > (pr / 2) && pg / 7 > (pb / 6)){
        if (det != GREEN){
          Serial.print("GREEN ");
          det = GREEN;
          if (last == BLUE){
            patt = (patt << 1) | 1;
            Serial.println("1");
          } else if (last == RED){
            patt = (patt << 1);
            Serial.println("0");
          }
          count ++;
        }
      } else if(pb / 3 > (pr / 2) && pb / 13 > (pg / 11)){
        if (det != BLUE){
          Serial.print("BLUE ");
          det = BLUE;
          if (last == RED){
            patt = (patt << 1) | 1;
            Serial.println("1");
          } else if (last == GREEN){
            patt = (patt << 1);
            Serial.println("0");
          }
          count ++;
        }
      } else if (pr > PCL && pg > PCL && pb > PCL){
        if(det != CLEAR){
          Serial.println("\nNo medium detected!");
          det = CLEAR;
        }
      }
    }
    last = det;
  } while (count < 9);
  count = 1;
  Serial.print("Received character: 0x");
  Serial.print(patt,HEX);
  Serial.print("- ");
  Serial.write(patt);
  Serial.println();
  patt = 0;
}
