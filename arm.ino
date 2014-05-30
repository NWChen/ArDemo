#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist;

int kBase = 12;
int kShoulder = 11;
int kElbow = 10;
int kWrist = 9;

int pBase = 3;
int pShoulder = 2;
int pElbow = 1;
int pWrist = 0;

void setup(){
  Serial.begin(9600);
  base.attach(kBase);
  shoulder.attach(kShoulder);
  elbow.attach(kElbow);
  wrist.attach(kWrist);
}

void loop(){
  base.write(pRead(pBase));
  shoulder.write(pRead(pShoulder));
  elbow.write(pRead(pElbow));
  wrist.write(pRead(pWrist));
  Serial.println(elbow.read());// + "/" + shoulder.read() + "/" + elbow.read() + "/" + wrist.read());
  delay(15);
}

int pRead(int pin){
  return map(analogRead(pin), 0, 600, 0, 179);
}

