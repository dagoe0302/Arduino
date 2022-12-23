#include <Arduino.h>
#line 1 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
// https://create.arduino.cc/projecthub/debanshudas23/getting-started-with-stepper-motor-28byj-48-3de8c9

#define A 2
#define B 3
#define C 4
#define D 5
 
#define NUMBER_OF_STEPS_PER_REV 512

#line 10 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void setup();
#line 18 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void write(int a,int b,int c,int d);
#line 26 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void onestep();
#line 46 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void loop();
#line 10 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void setup()
{
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
}

void write(int a,int b,int c,int d)
{
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void onestep()
{
  write(1,0,0,0);
  delay(5);
  write(1,1,0,0);
  delay(5);
  write(0,1,0,0);
  delay(5);
  write(0,1,1,0);
  delay(5);
  write(0,0,1,0);
  delay(5);
  write(0,0,1,1);
  delay(5);
  write(0,0,0,1);
  delay(5);
  write(1,0,0,1);
  delay(5);
}

void loop()
{
  int i;
  i=0;
  while(i<NUMBER_OF_STEPS_PER_REV)
  {
    onestep();
    i++;
  }
}
