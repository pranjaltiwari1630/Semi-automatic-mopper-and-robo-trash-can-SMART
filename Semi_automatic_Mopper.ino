#include <Servo.h>  // including servo motor library


int servoPin1=5; // declaring servo motor 1 pin
int servoPin2=6;  // declaring servo motor 2 pin
Servo Servo1;
Servo Servo2;

int en1=A0; //for speed control of motors
int en2=A1; //for speed control of motors
int n1=9; // for direction control of motors 
int n2=10; // for direction control of motors 
int n3=11; // for direction control of motors 
int n4=12; // for direction control of motors 
int en3=3; // for speed control of mopping motor 
int dir1=4;  //for direction control of mopping motor
int led=13; // LED to indicate whether the mopper is on or not
int pin=8; // for switching on the water pump (relay)
char t; // for enabling bluetooth module
int distance; // for calculating the distance via ultrasonic sensor
long duration;  // for calculating the duration via ultrasonic sensor
int trig=2;  // declaration of trigger pin
int echo=7;  // declaration of echo pin

void setup() {
  // put your setup code here, to run once:
pinMode(en1,OUTPUT);  // declaring the pin mode of wheel motors for speed
pinMode(en2,OUTPUT);  // declaring the pin mode of wheel motors for speed
pinMode(n1,OUTPUT);  // declaring the pin mode of wheel motors for direction
pinMode(n2,OUTPUT);  // declaring the pin mode of wheel motors for direction
pinMode(n3,OUTPUT);  // declaring the pin mode of wheel motors for direction
pinMode(n4,OUTPUT);  // declaring the pin mode of wheel motors for direction
pinMode(led,OUTPUT); // pin mode for LED
pinMode(pin,OUTPUT); //pin mode for relay
pinMode(en3,OUTPUT);  // declaring the pin mode of mopping motor for speed
pinMode(dir1,OUTPUT);  // declaring the pin mode of mopping motor for direction
pinMode(trig,OUTPUT);  //  declaring the pin mode of ultrasonic sensor trigger pin
pinMode(echo,INPUT);  //  declaring the pin mode of ultrasonic sensor echo pin


Serial.begin(9600);  // setting the baud rate for bluetooth module

Servo1.attach(servoPin1); // for using the servo pins
  Servo2.attach(servoPin2); // for using the servo pins
  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trig,LOW);  // initially the triger pin of ultrasonic sensor will be low
delay(100);
digitalWrite(trig,HIGH);   // Then the triger pin of ultrasonic sensor will be high
delay(100);
digitalWrite(trig,LOW);  // Then the triger pin of ultrasonic sensor will be low
duration=pulseIn(echo,HIGH);  // formula for calculation of duration in order to calculate the distance of the object
distance=duration*(0.034)/2;  // formula for calculation of distance of the object
Serial.print("distance=  ");
Serial.println(distance);

if (distance<=50)
{
  Serial.println("Dustbin opened");
  srvo1();
  delay(10);
  srvo2();
  delay(10);
}

 digitalWrite(led,LOW); // initially the LED will be low as the mopper is not started yet
 mopper(); // The mopper starts and remains running untill wait command is given
 digitalWrite(led,HIGH);  // LED starts glowing as the mottor starts
 if(Serial.available()) // Searching for bluetooth availability
 {
  t=Serial.read(); // getting the command from mobile via bluetooth
  Serial.println(t);  // for printing the command
  // put your main code here, to run repeatedly:
 }
 if(t=='1')  // Condition 1
{
  forward(); // The mopper drive will move forward
  digitalWrite(led,HIGH);
}
else if(t=='2') // Condition 2
 {
  back(); // The mopper drive will move backward
  digitalWrite(led,HIGH);
}
else if (t=='3') // Condition 3
{ right();  // The mopper drive will move right
digitalWrite(led,HIGH);
}
else if(t=='4') // Condition 4
{
  left();  // The mopper drive will move left
  digitalWrite(led,HIGH);
}
else if(t=='5') // Condition 5
{ wait();  // The mopper drive will stop
digitalWrite(led,HIGH);
}
else if(t=='6') // Condition 6
{ pump();  // The pump will release water
digitalWrite(led,HIGH);
}
else 
{ wait(); // Condition 7 the drive will remain still untill any command is given
}
delay(100);  // delay for 1 millisecond
}

void mopper() // function for mopper motor
{
  analogWrite(en3,100);
 digitalWrite(dir1,HIGH);
 Serial.println("Mopping the floor");
}



void srvo1()
  {
    Servo1.write(0);
  delay(1000);
  Servo1.write(180);
  delay(1000);
  Servo1.write(0);
  delay(1000);

  }
 void srvo2()
 {
  Servo2.write(0);
  delay(1000);
  Servo2.write(180);
  delay(1000);
  Servo2.write(0);
  delay(1000);
 }

 
void pump() // function for relay
{
  digitalWrite(pin,HIGH);
  delay(2000); 
  Serial.println("Releasing water for mopping");
  digitalWrite(pin,LOW);
  delay(2000);
}

void forward()  // function for wheel motor to move forward
{
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  analogWrite(en1,90);
  Serial.println("FORWARD");
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  analogWrite(en2,90);
  delay(100);
  
}


void back()  // function for wheel motor to move backward
{
digitalWrite(9,HIGH);
digitalWrite(10,LOW);
analogWrite(en1,90);
Serial.println("BACKWARD");
digitalWrite(11,HIGH);
digitalWrite(12,LOW);
analogWrite(en2,90);

}

void left()  // function for wheel motor to move left
{
digitalWrite(9,HIGH);
digitalWrite(10,LOW);
analogWrite(en1,70);
Serial.println("LEFT");
digitalWrite(11,LOW);
digitalWrite(12,HIGH);
analogWrite(en2,90);
}

void right()  // function for wheel motor to move right
{
digitalWrite(9,LOW);
digitalWrite(10,HIGH);
analogWrite(en1,90);
Serial.println("RIGHT");
digitalWrite(11,HIGH);
digitalWrite(12,LOW);
analogWrite(en2,70);
}

void wait()  // function for wheel motor to Wait 
{
digitalWrite(9,LOW);
digitalWrite(10,LOW);
analogWrite(en1,0);
Serial.println("WAITING");
digitalWrite(11,LOW);
digitalWrite(12,LOW);
analogWrite(en2,0);

}
