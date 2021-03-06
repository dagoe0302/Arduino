#include "Timer.h"
#include "System.h"

#define TIMER_VACANT -2    /* The timer is not in use */

typedef void (*P_TIMER_FUNC)(void);

static void SystemTimer(void);
//static void DisplayTimer(void);
static void Dht11Timer(void);
static void ButtonTimer(void);

const P_TIMER_FUNC timer_func_array[NOF_TIMERS] =
{
  SystemTimer,
  //DisplayTimer,
  Dht11Timer,
  ButtonTimer,
};

static long timeoutarray[NOF_TIMERS];

void StopTimer(TIMER_ID id)
{
  timeoutarray[id] = TIMER_VACANT;
}

void StartTimer(TIMER_ID id, long time_out)
{
  timeoutarray[id] = time_out;
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

void InitTimer()
{
  byte count;

  DisableInterrupts();//stop interrupts
  //cSystem.DisableInterrupts();//stop interrupts

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

  EnableInterrupts();//allow interrupts
}
// Set CS10 and CS12 bits for 1024 prescaler
//TCCR1B |= (1 << CS12) | (1 << CS10);

void SystemTimer(void)
{
  Notify(UPDATE_SYSTEM_TIME);
  StartTimer(SYSTEM_TIMER, ONE_SEC_TIMOUT);
}

//void DisplayTimer(void)
//{
//  cSystem.Notify(UPDATE_DISPLAY);
//  StartTimer(DISPLAY_TIMER, ONE_SEC_TIMOUT);
//}

void Dht11Timer(void)
{
  Notify(READ_TEMP);
  StartTimer(DHT11_TIMER, FIVE_SEC_TIMOUT);
}

void ButtonTimer(void)
{
  Notify(BUTTON_PUSHED);
 // StartTimer(BUTTON_TIMER, BUTTON_READ_TIMEOUT);
}
