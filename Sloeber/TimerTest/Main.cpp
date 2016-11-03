#include <Arduino.h>

#define TIMER_VACANT -2    /* The timer is not in use */
#define ONE_SEC_TIMOUT      100
#define PIN_LED       13
typedef void (*P_TIMER_FUNC)(void);

typedef enum
{
  SYSTEM_TIMER,
  /*DISPLAY_TIMER,
  DHT11_TIMER,
  BUTTON_TIMER,*/
  NOF_TIMERS
} TIMER_ID;

extern void SystemTimer(void);
/*extern void DisplayTimer(void);
extern void Dht11Timer(void);
extern void ButtonTimer(void);*/

const P_TIMER_FUNC timer_func_array[NOF_TIMERS] =
{
  SystemTimer,
 /* DisplayTimer,
  Dht11Timer,
  ButtonTimer,*/
};

static long timeoutarray[NOF_TIMERS];
byte LedToggle = 0;
byte test = 0;

void StartTimer(TIMER_ID id, long time_out)
{
  timeoutarray[id] = time_out;
}

void InitTimer()
{
  byte count;

  cli();//cSystem.DisableInterrupts();//stop interrupts

  for(count = 0; count < NOF_TIMERS; count++)
  {
    timeoutarray[count] = TIMER_VACANT;
  }

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 100hz increments
  OCR1A = 19999;// = (16*10^6) / (8*100) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //cSystem.EnableInterrupts();//allow interrupts
}

void HandleTimerTicks(void)
{
  byte count;

  for (count = 0; count < NOF_TIMERS; count++)
  {
    if(timeoutarray[count] > 0)
    {
      timeoutarray[count]--;
      if(timeoutarray[count] == 0)
      {
        timer_func_array[count]();
      }
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  HandleTimerTicks();
}

void SystemTimer(void)
{
/*  cSystem.Notify(UPDATE_SYSTEM_TIME); */

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
    test = 1;
    StartTimer(SYSTEM_TIMER, ONE_SEC_TIMOUT);
}

void Setup()
{
	  Serial.begin(9600);
	  Serial.println("Start");
	  // initialize digital pin 13 as an output.
	  pinMode(PIN_LED, OUTPUT);
	  //digitalWrite(PIN_LED, HIGH);
	  InitTimer();
	  StartTimer(SYSTEM_TIMER, ONE_SEC_TIMOUT);
}

void Main(void)
{
	  //Setup();

	/*  while(1)
	  {
		  Serial.println(test);
	  }*/
}
