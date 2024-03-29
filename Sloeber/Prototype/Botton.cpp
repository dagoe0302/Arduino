#include <Arduino.h>
#include "Timer.h"
#include "System.h"

boolean HasButtonBeenPushed = NO;

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
  StartTimer(BUTTON_TIMER, BUTTON_PUSH_TIMEOUT);
}

extern void InitButton(void)
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  //button pressed: read = HIGH; button not pressed: read = LOW;
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), iButtonPushed, HIGH);
}
