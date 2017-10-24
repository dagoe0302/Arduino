//pins
const byte Cinema_1_InputPin = 2;
const byte UpPin = 3;
const byte DownPin = 4;

//global interrupt state
volatile boolean interruptTriggered = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(Cinema_1_InputPin, INPUT_PULLUP);
  pinMode(UpPin, OUTPUT);
  digitalWrite(UpPin, LOW);
  pinMode(DownPin, OUTPUT);
  digitalWrite(DownPin, LOW);
  attachInterrupt(digitalPinToInterrupt(Cinema_1_InputPin), cinemaIsr, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (interruptTriggered == true)
  {
    boolean CinemaState = LOW;

    delay(1000); //simple debounce
    CinemaState = digitalRead(Cinema_1_InputPin);

    //insert delay here
    //delay(x);
    if (CinemaState == HIGH)
    {
      //move screen up
      digitalWrite(UpPin, HIGH);
      delay(200);
      digitalWrite(UpPin, LOW);
    }
    else
    {
      //CinemaState == LOW - move screen down
      digitalWrite(DownPin, HIGH);
      delay(200);
      digitalWrite(DownPin, LOW);
    }    
    interruptTriggered = false;
  }
}

//Interrupt Service Routine
void cinemaIsr()
{
  interruptTriggered = true;
}
