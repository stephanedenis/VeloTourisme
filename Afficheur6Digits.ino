#define DIGITS 6
#define SEGMENTS 7
#define SEGMENT_ON LOW
#define DIGIT_ON HIGH

const uint8_t digitCommonPins[DIGITS] = { // Right to left
  20,
  19,
  18,
  1,
  0,
  21
};

const uint8_t displayPins[SEGMENTS] = {
  7, //A
  15,//B
  16,//C
  14,//D
  8, //E
  9, //F
  10 //G
};

const byte font[] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

byte values[6]; //

void afficheurSetup() {
  for (byte digit = 0; digit < DIGITS; digit++) {
    pinMode(digitCommonPins[digit], OUTPUT);

    for (byte segment = 0; segment < SEGMENTS; segment++) {
      pinMode(displayPins[segment], OUTPUT);
    }
  }
}

void afficheSegment(byte targetDigit) {
  for (byte digit = 0; digit < DIGITS; digit++) {
    digitalWrite(digitCommonPins[digit], !DIGIT_ON);

    if (digit == targetDigit) {
      byte segments = font[values[digit]];

      for (byte segment = 0; segment < SEGMENTS; segment++) {
        if (segments & B00000001) {
          digitalWrite(displayPins[segment], SEGMENT_ON);
        }
        else {
          digitalWrite(displayPins[segment], !SEGMENT_ON);
        }
        segments >>= 1;
      }
      digitalWrite(digitCommonPins[digit], DIGIT_ON);
    }
  }
}

void refreshDisplay(){
    for (byte activeDigit = 0; activeDigit < DIGITS; activeDigit++) {
    afficheSegment(activeDigit);
    delay(3);
  }
}

void displayNumber(int number){
  int n=number;
  for (byte activeDigit = 0; activeDigit < DIGITS; activeDigit++) {
    values[activeDigit]=n%10;
    n/=10;
  }
}

