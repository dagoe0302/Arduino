#include <Arduino.h>
#include "Timer.h"
#include "System.h"

extern void SetButtonPush(void)
{
  HasButtonBeenPushed = YES;
}

extern void ClearButtonPush(void)
{
  HasButtonBeenPushed = NO;
}

extern boolean GetHasButtonBeenPushed(void)
{
  return (HasButtonBeenPushed);
}

void iButtonPushed(void)
{
 // digitalWrite(PIN_LED, LOW);
 // SetButtonPush();
 //Serial.println("ISR");
  //cSystem.Notify(BUTTON_PUSHED);
  StartTimer(BUTTON_TIMER, BUTTON_PUSH_TIMEOUT);
}

extern void InitButton(void)
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  //pinMode(PIN_BUTTON, INPUT);
  //digitalWrite(PIN_BUTTON, HIGH); //Turn on internal 20K pullup resistor
  //button pressed: read = HIGH; button not pressed: read = LOW;
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), iButtonPushed, HIGH);
}
