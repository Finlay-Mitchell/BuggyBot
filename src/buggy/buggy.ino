#include <HCSR04.h>

#define enableDebugOn

#define StatusLEDPin 2 //Every time we make an interaction, we flash this.
#define pinMotorDriveForward 3 //A-1A on H-Bridge
#define pinMotorDriveReverse 4 //A-1B on H-Bridge
#define pinMotorSteerLeft 5 //B-1A on H-Bridge
#define pinMotorSteerRight 6//B-1B on H-Bridge

#define pinTriggerUltrasonicCensor1 7
#define pinEchoUltrasonicCensor1 8
//#define pinTriggerUltrasonicCensor2 9
//#define pinEchoUltrasonicCensor2 10


HCSR04 s1(pinTriggerUltrasonicCensor1, pinEchoUltrasonicCensor1);
//HCSR04 s2(pinTriggerUltrasonicCensor2, pinEchoUltrasonicCensor2);

void setup()
{
  Serial.begin(9600); //Define the baud rate.
  pinMode(pinMotorDriveForward, OUTPUT);
  pinMode(pinMotorDriveReverse, OUTPUT);
  pinMode(pinMotorSteerLeft, OUTPUT);
  pinMode(pinMotorSteerRight, OUTPUT);

  // Stop the motors - HIGH = off, LOW = On
  digitalWrite(pinMotorDriveReverse, HIGH);
  digitalWrite(pinMotorDriveForward, HIGH);
  digitalWrite(pinMotorSteerLeft, HIGH);
  digitalWrite(pinMotorSteerRight, HIGH);

#ifdef enableDebugOn
  Serial.print("Startup - Version 1.1.1");
#endif
}

void SteerLeft(int delayInMillis)
{
  digitalWrite(StatusLEDPin, LOW);
  digitalWrite(StatusLEDPin, HIGH);

  digitalWrite(pinMotorSteerLeft, LOW);
  digitalWrite(pinMotorSteerRight, HIGH);
  delay(delayInMillis);
  digitalWrite(pinMotorSteerLeft, HIGH);
}

void SteerRight(int delayInMillis)
{
  digitalWrite(StatusLEDPin, LOW);
  digitalWrite(StatusLEDPin, HIGH);

  digitalWrite(pinMotorSteerLeft, HIGH);
  digitalWrite(pinMotorSteerRight, LOW);
  delay(delayInMillis);
  digitalWrite(pinMotorSteerRight, HIGH);
}

void DriveForward()
{
  digitalWrite(pinMotorDriveReverse, HIGH);
  digitalWrite(pinMotorDriveForward, LOW);
}

void StopDriving()
{
  digitalWrite(pinMotorDriveForward, HIGH);
  digitalWrite(pinMotorDriveReverse, HIGH);
}

void DriveBackwards();

void loop()
{
  DriveForward();
  Serial.print("S1 - ");
  Serial.println(s1.dist());
//  Serial.print("S2 - ");
//  Serial.println(s2.dist());
  
  if(s1.dist() <= 20 && s1.dist() >= 5 && s1.dist() != 0)
  {
    StopDriving();
    SteerRight(275);
  }
//
//  if(s2.dist() <= 20 && s2.dist() >= 5 && s2.dist() != 0)
//  {
//    StopDriving();
//    SteerLeft(275);
//  }
  
}
