#include <NewPing.h>
#include<Servo.h>
Servo myservo;
#define trig_pin A0 //analog input 0
#define echo_pin A1 //analog input 1
#define maximum_distance 200

NewPing sonar(trig_pin, echo_pin, maximum_distance);
// int enA = 10;
// int enB = 11;
const int RightMotorForward = 5;//IN4
const int RightMotorBackward = 4;//IN3
const int LeftMotorForward = 3;//IN2
const int LeftMotorBackward = 2;//IN1
char labview;

int data1;
int data2;
int data3;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
}

void loop()
{
  Serial.println("__________");
  labview = Serial.read();
  if (labview == '1')
  {
    autosensing();  //
    
  }
    else if(labview == 'S')
  {
    moveStop();
  }
}

int readPing()
{
  delay(45);
  int cm = sonar.ping_cm();
  return cm;
}

// void speed()
// {
//   int i = 150;
//   analogWrite(enA, i);
//   analogWrite(enB, i);
// }

void moveStop()
{
  Serial.println("MOTOR STOP");
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward()
{
  Serial.println("MOTOR MOVE FORWARD");
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW); 
  //speed();
}

void moveBackward()
{
  Serial.println("MOTOR MOVE BACK");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  //speed();
}
void moveright()
{
  Serial.println("MOTOR MOVE RIGHT");
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  //speed();
}
void moveleft()
{
  
  Serial.println("MOTOR MOVE LEFT");
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  //speed();
}

void servoright()
{

  myservo.write(0);
  Serial.println("LOOKING RIGHT");
  delay(500);
}

void servoleft()
{

Serial.println("LOOKING LEFT");
  myservo.write(180);
  delay(500);
}

void servofront()
{
  Serial.println("LOOKING FRONT");
  myservo.write(90);
  delay(500);
}

void autosensing()
{
  int data = readPing();
  if (data<30)
  {
    Serial.println("Searching...");
    moveStop();
    servoright();
    //Serial.println("less");
    data1 = readPing();
    //Serial.println(">>>>>>> RIGHT");
    //Serial.println(data1);
    
    servofront();
    data2 = readPing();
    //Serial.println(">>>>>>> FRONT");
    //Serial.println(data2);

    servoleft();
    data3 = readPing();
    //Serial.println(">>>>>>> LEFT");
    //Serial.println(data3);

    servofront();
    delay(100);
    
    if (data1>40)
    {
       moveBackward();
       delay(2000);
       moveright();
       delay(2000);
       moveForward();
       delay(1000);

       
    }
    else if (data2>40)
    {
      moveForward();
      delay(1000);

    }
    else if (data3>40)
    {
      moveBackward();
      delay(2000);
      moveleft();
      delay(2000);
      moveForward();
      delay(1000);
    }
  }
  else
  {
  moveForward();
  delay(100);
  }
}
