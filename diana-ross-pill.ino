int throatPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46};
int numWhite = 15;
int stringPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
int numStrings = 12;
int buttonPin = 52;

void setup() {
  int i;
  // put your setup code here, to run once:
  for(i = 0; i < numWhite; i++) {
    pinMode(throatPins[i], OUTPUT);
  }
  for(i = 0; i < numStrings; i++) {
    pinMode(stringPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  randomSeed(analogRead(0));
}

void loop() {
  int i, j;
  unsigned long startTime;

//  for(i = 0; i < numStrings; i++) {
//    digitalWrite(stringPins[i], HIGH);
//  }

  if(!digitalRead(buttonPin)) {
    // make the pill go down the throat
    for(i = 0; i <= numWhite; i++) {
      for(j = 0; j <= 255; j++) {
        if(i < numWhite) { // ramp up if we aren't at the end
          analogWrite(throatPins[i], j);
        }
        if(i > 0) { // ramp down if not at the beginning
          analogWrite((throatPins[i-1]), (255-j));
        }
        delay(1); // intentionally small, will make fade cycle longer
      }
    }
  
    // make the pill exploded in the stomach
    startTime = millis();
    // Blink lights for 10 seconds
    while((startTime + 10000) > millis()) {
      for(i = 0; i < numStrings; i++) {
        // randomly turn the stings on or off
        int x = random(0, 2);
        digitalWrite(stringPins[i], x);
      }
      delay(random(200, 500)); // wait to shuffle lights again
    }
    for(i = 0; i < numStrings; i++) {
      digitalWrite(stringPins[i], LOW); // reset lights
    }
  }
}
