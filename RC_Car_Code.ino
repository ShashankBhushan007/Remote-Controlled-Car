#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(8,13);


SoftwareSerial mySerial (10,12);   // rx, tx

float val2 = 0.0 ;

#define m1p 2
#define m1n 3
#define m2p 4
#define m2n 7

#define echopin 9
#define trigpin 11

#define enA 6
#define enB 5

void setup() {
  Serial.begin(9600);
  ArduinoUno.begin(4800);
  mySerial.begin(9600);
  pinMode(m1p, OUTPUT);
  pinMode(m1n, OUTPUT);
  pinMode(m2p, OUTPUT);
  pinMode(m2n, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void SpeedControl (char val){
  if (val == 's'){
    int i = 255;
    int j = 255;
    while (val == 's' && i>=0 && j>=0){
      analogWrite(enA, i);
      analogWrite(enB, j);
      digitalWrite(m1p, HIGH);
      digitalWrite(m1n, LOW);
      digitalWrite(m2p, HIGH);
      digitalWrite(m2n, LOW);
      delay(10);
      i-=10;
      j-=10;
      break;
    }
  }
  else if (val == 'a'){
    int i = 0;
    int j = 0;
    while (val == 'a' && i<=255 && j<= 255){
      analogWrite(enA, i);
      analogWrite(enB, j);
      digitalWrite(m1p, HIGH);
      digitalWrite(m1n, LOW);
      digitalWrite(m2p, HIGH);
      digitalWrite(m2n, LOW);
      delay(10);
      i+=10;
      j+=10;
      break;
      }
    }
  else if (val == 'f'){
    digitalWrite(m1p, HIGH);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, HIGH);
    digitalWrite(m2n, LOW);
    delayMicroseconds(2);
    delay(10);
  }
  else if (val == 'l'){
    digitalWrite(m1p, HIGH);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, LOW);
    digitalWrite(m2n, LOW);
    delayMicroseconds(2);
  }
  else if (val == 'r'){
    digitalWrite(m1p, LOW);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, HIGH);
    digitalWrite(m2n, LOW);
    delayMicroseconds(2);
  }
  else if (val == 'b'){
    digitalWrite(m1p, LOW);
    digitalWrite(m1n, HIGH);
    digitalWrite(m2p, LOW);
    digitalWrite(m2n, HIGH );
    delayMicroseconds(2);
  }
  delayMicroseconds(2);
}












void automated (int calculateddistance){
  if (calculateddistance < 5){
    analogWrite(enA, 50);
    analogWrite(enB, 50);
    digitalWrite(m1p, LOW);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, LOW);
    digitalWrite(m2n, LOW);
    delayMicroseconds(5);
  }
  else if (calculateddistance >=20){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(m1p, HIGH);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, HIGH);
    digitalWrite(m2n, LOW);
    delayMicroseconds(5);
  }
  else {
    analogWrite(enA, 150);
    analogWrite(enB, 150);
    digitalWrite(m1p, HIGH);
    digitalWrite(m1n, LOW);
    digitalWrite(m2p, HIGH);
    digitalWrite(m2n, LOW);
    delayMicroseconds(5);
    
  }
  delay(500);
}





void loop() {
  while(ArduinoUno.available()>0) {
    //to get data from nodemcu
    float val2 = ArduinoUno.parseFloat();
    if(ArduinoUno.read() == '\n') {
      Serial.println(val2);
    }
  }
  int calculateddistance;
  long long measuredistance;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(5);
  measuredistance = pulseIn(echopin, HIGH);
  calculateddistance = (0.034 * measuredistance) / 2; // in cm

  if ((val2 == 1) && (mySerial.available())){
    delayMicroseconds(2);
    char val = mySerial.read();
    SpeedControl(val);
  }
  else if (val2 == 2){
    automated(calculateddistance);
  }
  delay(10);
}