#include <SoftwareSerial.h>
SoftwareSerial mySerial(A0, A1); //rx, tx

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  mySerial.begin(115200);
  for (int i = 0; i < 14; i++ ) {
    pinMode(i , OUTPUT);
    digitalWrite(i, LOW);
  }
  randomSeed(analogRead(2));

}

void loop() {
  // put your main code here, to run repeatedly:
  if ( mySerial.available() ) {
    char received = mySerial.read();
    Serial.println(received);
    if ( received == '0') {
      Serial.println("All Off");
      allOff();
    }
    if ( received == '1') {
      Serial.println("All on");
      allOn();
    }
    if ( received == '2') {
      Serial.println("Cycle");
      goThroughAll();
    }
    if (received == '3') {
      Serial.println("Single");
      oneByOne();
    }
    if (received == '4') {
      Serial.println("Single Off");
      oneByOneOff();
    }
    if (received == '5') {
      Serial.println("Blinky");
      blinky(5, 500);
    }
    if (received == '6') {
      Serial.println("Two Sides");
      twoSides();
    }
    if (received == '7') {
      Serial.println("Two Sides Off");
      twoSidesOff();
    }
    if (received == '8') {
      Serial.println("PWM");
      PWM();
    }
    if (received == '9') {
      Serial.println("Random Lights");
      randomLight();
    }
    if (received == 'A') {
      Serial.println("Random Lights Off");
      randomLightOff();
    }
  }
}

void goThroughAll() {
  oneByOne();
  delay(2000);
  oneByOneOff();
  blinky(5, 500);
  twoSides();
  delay(2000);
  twoSidesOff();
  PWM();
  PWM();
  allOff();
  randomLight();
  delay(1000);
  randomLightOff();
  randomLight();
  delay(1000);
  randomLightOff();
}

void oneByOne() {
  for (int i = 3; i < 14; i++) {
    digitalWrite(i, HIGH);
    delay(100);
  }
  for (int j = 0; j < 3; j++) {
    digitalWrite(j, HIGH);
    delay(100);
  }
}

void oneByOneOff() {
  for (int i = 3; i < 14; i++) {
    digitalWrite(i, LOW);
    delay(100);
  }
  for (int j = 0; j < 3; j++) {
    digitalWrite(j, LOW);
    delay(100);
  }
}

void allOff() {
  for (int i = 3; i < 14; i++) {
    digitalWrite(i, LOW);
  }
  for (int j = 0; j < 3; j++) {
    digitalWrite(j, LOW);
  }
}

void allOn() {
  for (int i = 3; i < 14; i++) {
    digitalWrite(i, HIGH);
  }
  for (int j = 0; j < 3; j++) {
    digitalWrite(j, HIGH);
  }
}

void blinky(int times, int delayT) {
  for (int i = 0; i < times + 1; i++) {
    allOn();
    delay(delayT);
    allOff();
    delay(delayT);
  }
}

void twoSides() {
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(4, HIGH); digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(5, HIGH); digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(6, HIGH); digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(7, HIGH); digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(8, HIGH); digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(9, HIGH); digitalWrite(11, HIGH);
  delay(500);
  digitalWrite(10, HIGH);
  delay(500);
}

void twoSidesOff() {
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(9, LOW); digitalWrite(11, LOW);
  delay(500);
  digitalWrite(8, LOW); digitalWrite(12, LOW);
  delay(500);
  digitalWrite(7, LOW); digitalWrite(13, LOW);
  delay(500);
  digitalWrite(6, LOW); digitalWrite(0, LOW);
  delay(500);
  digitalWrite(5, LOW); digitalWrite(1, LOW);
  delay(500);
  digitalWrite(4, LOW); digitalWrite(2, LOW);
  delay(500);
  digitalWrite(3, LOW);
  delay(500);

}

void PWM() {
  for (int i = 0; i < 200; i++) {
    analogWrite(3, i);
    analogWrite(5, i);
    analogWrite(6, i);
    analogWrite(9, i);
    analogWrite(10, i);
    analogWrite(11, i);
    delay(10);
  }

  for (int j = 200; j > 0; j--) {
    analogWrite(3, j);
    analogWrite(5, j);
    analogWrite(6, j);
    analogWrite(9, j);
    analogWrite(10, j);
    analogWrite(11, j);
    delay(10);
  }
}

void randomLight() {
  int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  int count = 14;
  scrambleArray(numbers, count);
  for ( int i = 0; i < count; i++ ) {
    digitalWrite(numbers[i], HIGH);
    delay(100);
  }
}

void randomLightOff() {
  int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
  int count = 14;
  scrambleArray(numbers, count);
  for ( int i = 0; i < count; i++ ) {
    digitalWrite(numbers[i], LOW);
    delay(100);
  }
}

void scrambleArray( int * array, int size ) {
  int last = 0;
  int temp = array[last];
  for ( int i = 0; i < size; i++ ) {
    int index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}
