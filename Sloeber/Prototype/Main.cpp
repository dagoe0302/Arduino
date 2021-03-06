#include <Arduino.h>
#include "System.h"
#include "Timer.h"
#include "Display.h"
#include "Temperature.h"
#include "Button.h"

boolean LedToggle = 0;
static NOTIFY_ELEMENT_TYPE input;

void Setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(PIN_LED, OUTPUT); // initialize digital pin 13 as an output.
  digitalWrite(PIN_LED, HIGH);
  InitDisplay();
  InitTemperature();
  InitSystemTime();
  InitButton();
  InitTimer();
  StartTimer(SYSTEM_TIMER, ONE_SEC_TIMOUT);
  StartTimer(DHT11_TIMER, FIVE_SEC_TIMOUT);
  // init done
}

void MainLoop(void)
{
  input = GetNotifyList();

  switch(input)
  {
    case UPDATE_SYSTEM_TIME: //SystemTimer notify
    {
   	  UpdateSystemTime();
      if (LedToggle == 1)
      {
        digitalWrite(PIN_LED, HIGH);
        LedToggle = 0;
      }
      else
      {
        digitalWrite(PIN_LED, LOW);
        LedToggle = 1;
      }
      Notify(UPDATE_DISPLAY);
      ClearNotify(UPDATE_SYSTEM_TIME);
    }
    break;

    case UPDATE_DISPLAY: //DisplayUpdate notify
	{
	  static uint8_t display_view_no = 0;

	  if (GetHasButtonBeenPushed() == YES)
	  {
	   	display_view_no = UpdateDisplayViewNo();
	    ClearButtonPush();
	  }
	  DisplayUpdate(display_view_no);
	  ClearNotify(UPDATE_DISPLAY);
	}
	break;

    case READ_BUTTON: //Button notify
    {
	  Notify(UPDATE_DISPLAY);
	  ClearNotify(READ_BUTTON);
	}
	break;

	case BUTTON_PUSHED: // Button has been pushed
	{
	  if (digitalRead(PIN_BUTTON) == HIGH)
	  {
	    // button still pushed
	    StartTimer(BUTTON_TIMER, BUTTON_PUSH_TIMEOUT);
      }
	  else // button has been releashed for 50 ms
	  {
        // button released
	    SetButtonPush();
	    Notify(UPDATE_DISPLAY);
	    ClearNotify(BUTTON_PUSHED);
      }
	}
	break;

    case READ_TEMP:
    {
      ReadTemperature();
      Notify(UPDATE_DISPLAY);
      ClearNotify(READ_TEMP);
    }
    break;

    default:
	{

	}
	break;
  }
}
