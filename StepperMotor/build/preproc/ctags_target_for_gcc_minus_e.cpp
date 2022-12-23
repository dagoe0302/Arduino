# 1 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
// https://create.arduino.cc/projecthub/debanshudas23/getting-started-with-stepper-motor-28byj-48-3de8c9
# 10 "/Users/mikaelsmacbook/Documents/projects/Arduino/StepperMotor/StepperMotor.ino"
void setup()
{
  pinMode(2,0x1);
  pinMode(3,0x1);
  pinMode(4,0x1);
  pinMode(5,0x1);
}

void write(int a,int b,int c,int d)
{
  digitalWrite(2,a);
  digitalWrite(3,b);
  digitalWrite(4,c);
  digitalWrite(5,d);
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
  while(i<512)
  {
    onestep();
    i++;
  }
}
