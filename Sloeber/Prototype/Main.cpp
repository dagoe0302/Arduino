#include <Arduino.h>
#include "System.h"
#include "Timer.h"
#include "Display.h"
#include "Temperature.h"
#include "Button.h"


//System cSystem;

boolean HasButtonBeenPushed = NO;
boolean LedToggle = 0;
static NOTIFY_ELEMENT_TYPE input;
//unsigned long lastDebounceTime = 0;
//unsigned long debounceDelay = 100;

long test_read = 0;

void Setup()
{
  //byte count;
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  // initialize digital pin 13 as an output.
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  InitDisplay();
  InitTemperature();
  InitSystemTime();
  InitButton();
  //DisplayUpdate(0);
  //delay(1000); //to have a nice 1st time display update
  InitTimer();
  StartTimer(SYSTEM_TIMER, ONE_SEC_TIMOUT);
  StartTimer(DHT11_TIMER, FIVE_SEC_TIMOUT);
  //StartTimer(DISPLAY_TIMER, ONE_SEC_TIMOUT);
  //StartTimer(BUTTON_TIMER, BUTTON_READ_TIMEOUT);
  /*Serial.println("Timeout Array:");
  for (count = 0; count < NOF_TIMERS; count++)
  {
    Serial.println(timeoutarray[count]);
  }*/
  /*Serial.println(timeoutarray[1]);
  Serial.println(timeoutarray[2]);
  Serial.println(timeoutarray[3]);*/
  //Serial.println("Init done");
  // init done
}

void MainLoop(void)
{
  //Setup();

  /*while(1)
  {*/
    input = GetNotifyList();
    //Serial.println("GetNotifyList");
    //Serial.println(timeoutarray[SYSTEM_TIMER]);
    //Serial.println(test_read);
    //test_read = timeoutarray[SYSTEM_TIMER];
    switch(input)
    {
      case UPDATE_SYSTEM_TIME://SystemTimer notify
      {
    	//Serial.println("Update system time");
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
	 /*     if (digitalRead(PIN_BUTTON) == HIGH)
	    {
	      HasButtonBeenPushed = YES;
	    }*/
	    Notify(UPDATE_DISPLAY);
	    ClearNotify(READ_BUTTON);
	  }
	  break;

	  case BUTTON_PUSHED: // Button has been pushed
	  {
	    Serial.println("Pushed");
	    if (digitalRead(PIN_BUTTON) == HIGH)
	    {
	      Serial.println("HIGH");
	      // button still pushed
	      //lastDebounceTime = millis();
	      StartTimer(BUTTON_TIMER, BUTTON_PUSH_TIMEOUT);
	    }
	    else // button has been releashed for 50 ms
	    {
          /*unsigned long milisec = millis();

	      Serial.println(milisec);
	      Serial.println(lastDebounceTime);*/
	      // button released or bouncing
	      //if ((millis() - lastDebounceTime) > debounceDelay)
	      //{
	        // button released
	        Serial.println("Released");
	        SetButtonPush();
	        Notify(UPDATE_DISPLAY);
	        ClearNotify(BUTTON_PUSHED);
	     // }
	      // else do nothing - still debouncing
	    }
	  }
	  break;

      case READ_TEMP:
      {
    	ReadTemperature();
        //Serial.print(HeatIndex);
        Notify(UPDATE_DISPLAY);
        ClearNotify(READ_TEMP);
      }
      break;

      default:
	  {

	  }
	  break;
    }
  //}
}
