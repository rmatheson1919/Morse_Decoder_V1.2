#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Times
int long t1;
int long t2;
int long t3;
int long onLength;
int long offLength;

//inputs
int b1 = 9;
int b2 = 8;

//outputs
int ledPin = 13;
int buzzerPin = 12;

int buzzerFr = 1000;

//strings
String code;
String character;
String letter;



void setup() {
  //setup buttons
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  //setup outputs
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, INPUT);

  //setup lcd
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-Morse  Decoder-");
  lcd.setCursor(0, 1);
  lcd.print("Hit B2  to Start");

  //setup main screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-Morse  Decoder-");
  lcd.setCursor(0, 1);
  lcd.print("Hit B2  to Start");
  delay(500);

  //if b2 is pressed move forward
  while (digitalRead(b2) == 0) delay(50);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Input Morse Code");

  //read inputs
  while (digitalRead(b1) == LOW) delay(1);
  lcd.clear();

}

void loop(){
  //wait untill b1 is pressed
  while (digitalRead(b1) == LOW) delay(1);

  //log when button is pressed
  t1 = millis();

  //when buttonme is high, trun on buzzer and led
  while (digitalRead(b1) == HIGH) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, buzzerFr);
  }

  // log when button is released
  t2 = millis();

  //calculate time on
  onLength = t2 - t1;

  // return the dot/dash based on press length
  if (onLength > 50) {
    character = readInput(onLength);
    code += character;
    lcd.print(character);
  }

  // while b1 is low, shut off led and buzzer
  while (digitalRead(b1) == LOW) {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  // log when button is pressed again
  t3 = millis();

  //get how long buttone is off for
  offLength = t3 - t2;

  //if b1 isnt pressed for 8/10 of a second, read code and output letter
  if (offLength > 800) {
    letter += readLetter(code);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(letter);
    lcd.setCursor(0, 0);
    code = "";
    if (letter.length() >= 16) letter = "";
  }
}

//read input and output dot/dash
String readInput(int x) {
  if (x >= 50 && x < 250) return ".";
  else if (x > 250 && x <= 800) return "-";
  else if (x > 800) return "";
}

//read code and output letter/number/symbol
String readLetter(String x) {

  //letters
  if (x == ".-") return "A";
  else if (x == "-...") return "B";
  else if (x == "-.-.") return "C";
  else if (x == "-..") return "D";
  else if (x == ".") return "E";
  else if (x == "..-.") return "F";
  else if (x == "--.") return "G";
  else if (x == "....") return "H";
  else if (x == "..") return "I";
  else if (x == ".---") return "J";
  else if (x == "-.-") return "K";
  else if (x == ".-..") return "L";
  else if (x == "--") return "M";
  else if (x == "-.") return "N";
  else if (x == "---") return "O";
  else if (x == ".--.") return "P";
  else if (x == "--.-") return "Q";
  else if (x == ".-.") return "R";
  else if (x == "...") return "S";
  else if (x == "-") return "T";
  else if (x == "..-") return "U";
  else if (x == "...-") return "V";
  else if (x == ".--") return "W";
  else if (x == "-..-") return "X";
  else if (x == "-.--") return "Y";
  else if (x == "--..") return "Z";

  //Numbers
  else if (x == "-----") return "0";
  else if (x == ".----") return "1";
  else if (x == "..---") return "2";
  else if (x == "...--") return "3";
  else if (x == "....-") return "4";
  else if (x == ".....") return "5";
  else if (x == "-....") return "6";
  else if (x == "--...") return "7";
  else if (x == "---..") return "8";
  else if (x == "----.") return "9";

  //characters
  else if (x == "--..--") return ",";
  else if (x == ".-.-.-") return ".";
  else if (x == "..--..") return "?";
  else if (x == "-.-.-.") return ";";
  else if (x == "---...") return ":";
  else if (x == "-..-.") return "/";
  else if (x == "-....-") return "-";
  else if (x == ".----.") return "'";
  else if (x == "..--.-") return "_";
  else if (x == "-.--.") return "(";
  else if (x == "-.--.-") return ")";
  else if (x == "-...-") return "=";
  else if (x == ".-.-.") return "+";
  else if (x == "_.._") return "*";
  else if (x == ".--.-.") return "@";
  else if (x == "...---...") return "SOS";

  else return "?";
}
