// Authors : Antonios Glioumpas & Nikiforos Paraskevopoulos
// version : 6
// date: 15 March 2015
//
// Description: 
// This is the file to be transferred to the Arduino Board
// Before compiling, make sure that all pins are connected according to the schematics


#include <Servo.h>
#include <SoftwareSerial.h>
#define RxD 0    //receive data on digital 0
#define TxD 1 //transmit on digital 1

SoftwareSerial blueToothSerial(RxD, TxD);
Servo elbow;
Servo gripper;
Servo camHor;
Servo camVer;
char receivedChar;

int vSpeed = 0;
int LED = 2 ;

// Connect motor controller pins to Arduino digital pins
// motor A
int enA = 6;
int in1 = 8;
int in2 = 9;
// motor B
int in3 = 4;
int in4 = 7;
int enB = 5;
// Manually abjust the following values for maximum optimality :
int DefenAF = 0;//40
int DefenAB = 0;//15
int vSpeedAnalogy = 1 ;
//Default Values: Camera
int defPosCamHor = 80  ;
int defPosCamVer = 100 ;
//Default Values: Gripper
int def_Elbow_down = 40;
int def_Elbow_up = 100;
int def_Gripper_Open = 75;
int def_Gripper_Closed = 0;
int receivedCharInt;

void setup()
{ // set all the motor control pins to outputs
  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT);
  
  elbow.attach(11);    elbow.write(def_Elbow_down);
  gripper.attach(10);    gripper.write(def_Gripper_Open);
  
  camVer.attach(12);    camVer.write(defPosCamVer);
  camHor.attach(13);    camHor.write(defPosCamHor);
  }

void loop() {

  if (Serial.available() > 0) { // stay here as long as COM port is empty
    receivedChar = blueToothSerial.read();
    receivedCharInt = Serial.parseInt();
    
    Serial.print(" bluetooth serial: ");
    Serial.println(receivedCharInt);
    Serial.print(" serial read: " );
    Serial.println(int(receivedChar));
	
  // CAMERA CONTROL - 1 SERVO MOTOR

      Serial.println(defPosCamVer);
      if ( receivedChar == 112) {
        defPosCamVer = defPosCamVer + 1;
        camVer.write(defPosCamVer);
      }
      else if ( receivedChar == 113) {
        defPosCamVer = defPosCamVer - 1;
        camVer.write(defPosCamVer);
      }
      else if ( receivedChar == 104) {
        defPosCamHor = defPosCamHor + 1;
        camHor.write(defPosCamHor);
      }
      else if ( receivedChar == 105) {
        defPosCamHor = defPosCamHor - 1;
        camHor.write(defPosCamHor);
      }
       

  // --- ELBOW CONTROL - 1 SERVO MOTOR ---
  if (receivedChar == 117) {
    elbow.write(def_Elbow_up);
  }
  else if (receivedChar == 116) {
    elbow.write(def_Elbow_down);
  }
  if (receivedChar == 119) {
    gripper.write(def_Gripper_Open);
  }
  else if (receivedChar == 118) {
    gripper.write(def_Gripper_Closed);
  }
   if (receivedChar == 120) {
    digitalWrite(LED,HIGH);
  }
  else if (receivedChar == 121) {
    digitalWrite(LED,LOW);
  }

  // --- CHANGE OF PLATFORM SPEED ---
  // if the state of receivedChar is equal from 0 to 4. 
  // Values must be from 0 to 255 (PWM)
  if (receivedChar == 0) {
    vSpeed = 0;
  }
  else if (receivedChar == 1) {
    vSpeed = 45;
  }
  else if (receivedChar == 2) {
    vSpeed = 60;
  }
  else if (receivedChar == 3) {
    vSpeed = 75;
  }
  else if (receivedChar == 4) {
    vSpeed = 100;
  }
  else if (receivedChar == 5) {
    vSpeed = 125;
  }
  else if (receivedChar == 6) {
    vSpeed = 150;
  }
  else if (receivedChar == 7) {
    vSpeed = 175;
  }
  else if (receivedChar == 8) {
    vSpeed = 200;
  }
  else if (receivedChar == 9) {
    vSpeed = 225;
  }
  else if (receivedChar == 10) {
    vSpeed = 250;
  }
 
 
 // --- PLATFORM MOVEMENT ---
 //If the receivedChar from the Arduino Bluetooth RC Car  App is equal with letter 'F', the car will go forward.
  if (receivedChar == 'F') { // this function will run the motors in both directions at a fixed speed
    digitalWrite(in1, LOW);  // turn on motor A
    digitalWrite(in2, HIGH); 
    analogWrite(enA, vSpeed + (vSpeed && 1)*DefenAF);
    digitalWrite(in3, LOW);  // turn on motor B
    digitalWrite(in4, HIGH);
    analogWrite(enB, vSpeed);
  }
  //If the receivedChar from the Arduino Bluetooth RC Car  App is equal with letter 'B', the car will go back.
  else if (receivedChar == 'B') {
    digitalWrite(in1, HIGH);  // turn on motor A on reverse direction
    digitalWrite(in2, LOW);   
    analogWrite(enA, vSpeed + (vSpeed && 1)*DefenAB );
    digitalWrite(in3, HIGH);  // turn on motor B on reverse direction
    digitalWrite(in4, LOW);
    analogWrite(enB, vSpeed);
  }
  //If the receivedChar from the Arduino Bluetooth RC Car  App is equal with letter 'L', the car will go to the left.
  else if (receivedChar == 'L') {
    digitalWrite(in1, LOW);   // turn on motor A on reverse direction
    digitalWrite(in2, HIGH);  
    analogWrite(enA, vSpeed  + (vSpeed && 1)*DefenAF);
    digitalWrite(in3, HIGH);  // turn on motor B 
    digitalWrite(in4, LOW);
    analogWrite(enB, vSpeed);
  }
  //If the receivedChar from the Arduino Bluetooth RC Car App is equal with letter 'R', the car will go to the right.
  else if (receivedChar == 'R') {
    digitalWrite(in1, HIGH);  // turn on motor A 
    digitalWrite(in2, LOW);
    analogWrite(enA, vSpeed  + (vSpeed && 1)*DefenAB );
    digitalWrite(in3, LOW);  // turn on motor B on reverse direction
    digitalWrite(in4, HIGH);
    analogWrite(enB, vSpeed);
  }
}
// If no signal from the bluetooth is received, don't move the motors
  else {
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
}
