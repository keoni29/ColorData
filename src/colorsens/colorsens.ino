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
  static unsigned int rr, gg, bb, det = NONE, last = NONE, patt = 0, count = 0;
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
  if (rr < 880 && gg < 900 && bb < 800){
    if (rr > 700 && gg < 450 && bb < 350){
      if (det != RED){
        Serial.println("Color RED detected!");
        det = RED;
      }
    } else if (rr < 550 && gg > 720 && bb < 520){
      if (det != GREEN){
        Serial.println("Color GREEN detected!");
        det = GREEN;
      }
    } else if (rr < 400 && bb > 600){
      if (det != BLUE){
        Serial.println("Color BLUE detected!");
        det = BLUE;
      }
    } else if (rr < 150 && bb < 150 && gg < 150){
      if (det != BLACK){
        Serial.println("Black detected!");
        det = BLACK;
      }
    } else {
      if (det != NONE){
        Serial.println("No color detected!");
        det = NONE;
      }
    }
  } else {
    if (det != CLEAR){
      Serial.println("No medium detected!");
      det = CLEAR;
    }
  }
  
  if (det != NONE && det != CLEAR){
    if (det != last){
      switch (det){
      case BLACK: patt = 0;
                  count = 0;
                  Serial.println("Clear");
                  break;
      case RED: if (last == GREEN){
                  patt = (patt << 1) | 1;
                  Serial.println("ONE");
                } else if (last == BLUE){
                  patt = (patt << 1);
                  Serial.println("ZERO");
                }
                count ++;
                break;
      case GREEN: if (last == BLUE){
                  patt = (patt << 1) | 1;
                  Serial.println("ONE");
                } else if (last == RED){
                  patt = (patt << 1);
                  Serial.println("ZERO");
                }
                count ++;
                break;
      case BLUE: if (last == RED){
                  patt = (patt << 1) | 1;
                  Serial.println("ONE");
                } else if (last == GREEN){
                  patt = (patt << 1);
                  Serial.println("ZERO");
                }
                count ++;
                break;
      }
      Serial.print("Counter is:");
      Serial.println(count);
    }
    if (count == 9){
      count = 1;
      Serial.print("Received character: 0x");
      Serial.print(patt,HEX);
      Serial.print("- ");
      Serial.write(patt);
      Serial.println();
      patt = 0;
    }
    last = det;
  }
  // Use this code to calibrate
  /*
  Serial.print("Red:");
  Serial.print(rr);
  Serial.print(" Green:");
  Serial.print(gg);
  Serial.print(" Blue:");
  Serial.println(bb);
  */
}
