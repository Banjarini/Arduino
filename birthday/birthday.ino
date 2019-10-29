//RED 9;
//BLUE 10;
//WHITE 11; 

#include "pitches.h"
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};
//notes in the melody
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

//note durations: 4 = quarter note, 8 = eight note, etc.
int noteDurations[] = {
  8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 2, 
};
int brightness = 100;
bool state = true;
void setup() {
  randomSeed(analogRead(0));
  lcd.begin(16, 2);
  
  // create a new character
  lcd.createChar(3, armsDown);
  // create a new character
  lcd.createChar(4, armsUp);
  
  lcd.setCursor(0, 0);
  // Print a message to the lcd.
  lcd.print("Happy Birthday ");
  lcd.setCursor(0,1);
  lcd.print("Katy");
  
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
  digitalWrite(12,LOW);
  
  for (int thisNote = 0 ; thisNote < 25 ; thisNote++) {
    if(state == true){
    state = false;
    lcd.setCursor(5, 1);
    // draw the little man, arms down:
    lcd.write(3);
  }
  else{
    state = true;
    lcd.setCursor(5, 1);
    // draw him arms up:
    lcd.write(4);
  }
    int randomLight1 = random(9, 12);
    int randomLight2 = random(9, 12);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite (randomLight1, brightness);
    digitalWrite (randomLight2, brightness);
    //digitalWrite (random(9, 12), LOW);
    
    int noteDuration = 1130/noteDurations[thisNote];
    tone (8, melody[thisNote], noteDuration);
    
    int pause = noteDuration * 1.275;
    delay (pause);
    
    noTone(3);

    
  }

  delay(3000);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    
}

void loop() {
  //no need to repeat

}
