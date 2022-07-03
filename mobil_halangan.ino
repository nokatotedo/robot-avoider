#include <Servo.h>

int echoPin = 9;
int trigPin = 8;
int pwmPinA = 3;
int pwmPinB = 11;
int inSatuA = 5;
int inSatuB = 4;
int inDuaA = 7;
int inDuaB = 6;
int servoPin = 12;

long duration;
int distance;
int pwmA = 200;
int pwmB = 105;
int pwmPelanA = 200;
int pwmPelanB = 105;
int kiri = 0;
int kanan = 0;
int jumlahKanan = 0;
Servo servo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(inSatuA, OUTPUT);
  pinMode(inSatuB, OUTPUT);
  pinMode(inDuaA, OUTPUT);
  pinMode(inDuaB, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(90);
}

void sensorOn() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
}

void maju() {
  digitalWrite(inSatuA, HIGH);
  digitalWrite(inSatuB, LOW);
  digitalWrite(inDuaA, LOW);
  digitalWrite(inDuaB, HIGH);
  analogWrite(pwmPinA, pwmA);
  analogWrite(pwmPinB, pwmB);
}

void majuPelan() {
  analogWrite(pwmPinA, pwmPelanA);
  analogWrite(pwmPinB, pwmPelanB);
  digitalWrite(inSatuA, HIGH);
  digitalWrite(inSatuB, LOW);
  digitalWrite(inDuaA, LOW);
  digitalWrite(inDuaB, HIGH);
}

void majuKiri() {
  analogWrite(pwmPinA, 200);
  analogWrite(pwmPinB, 200);
  digitalWrite(inSatuA, HIGH);
  digitalWrite(inSatuB, LOW);
  digitalWrite(inDuaA, HIGH);
  digitalWrite(inDuaB, LOW);
  delay(800);
}

void majuKanan() {
  analogWrite(pwmPinA, 200);
  analogWrite(pwmPinB, 200);
  digitalWrite(inSatuA, LOW);
  digitalWrite(inSatuB, HIGH);
  digitalWrite(inDuaA, LOW);
  digitalWrite(inDuaB, HIGH);
  jumlahKanan++;
  delay(640);
}

void mundur() {
  analogWrite(pwmPinA, 160);
  analogWrite(pwmPinB, 150);
  digitalWrite(inSatuA, LOW);
  digitalWrite(inSatuB, HIGH);
  digitalWrite(inDuaA, HIGH);
  digitalWrite(inDuaB, LOW);
  delay(2000);
}

void servoOn() {
  delay(500);
  servo.write(0);
  delay(1000);
  sensorOn();
  if(distance >= 30) {
    kanan = 0;
  }
  if(distance < 30) {
    kanan = 1;
  }
  delay(500);
  servo.write(180);
  delay(1000);
  sensorOn();
  if(distance >= 30) {
    kiri = 0;
  }
  if(distance < 30) {
    kiri = 1;
  }
  delay(500);
  servo.write(90);
  delay(1000);
}

void henti() {
  digitalWrite(inSatuA, LOW);
  digitalWrite(inSatuB, LOW);
  digitalWrite(inDuaA, LOW);
  digitalWrite(inDuaB, LOW);
  analogWrite(pwmPinA, 0);
  analogWrite(pwmPinB, 0);
}

void loop() {
  sensorOn();
  if(distance >= 100) {
    maju();
  }
  if((distance > 30)&&(distance < 100)) {
    majuPelan();
  }
  if((distance >= 1)&&(distance <= 30)) {
    henti();
    servoOn();
    if((kiri == 0)&&(kanan == 0)) {
      Serial.println("Kiri dan Kanan terbuka");
      majuKanan();
    } else if((kiri == 0)&&(kanan == 1)) {
      Serial.println("Kiri terbuka");
      majuKiri();
      kanan = 0;
    } else if((kiri == 1)&&(kanan == 0)) {
      Serial.println("Kanan terbuka");
      majuKanan();
      kiri = 0;
    } else if((kiri == 1)&&(kanan == 1)) {
      Serial.println("Kanan dan Kiri tertutup");
      mundur();
      kiri = 0;
      kanan = 0;
    }
  }
  if(jumlahKanan == 5) {
    majuKiri();
    delay(1300);
    jumlahKanan = 0;
  }
}
