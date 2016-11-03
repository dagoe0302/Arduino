
#define ONE_SEC_TIMOUT      100
#define FIVE_SEC_TIMOUT     500
#define BUTTON_PUSH_TIMEOUT  30

typedef enum
{
  SYSTEM_TIMER,
  DISPLAY_TIMER,
  DHT11_TIMER,
  BUTTON_TIMER,
  NOF_TIMERS
} TIMER_ID;

extern void StopTimer(TIMER_ID id);
extern void StartTimer(TIMER_ID id, long time_out);
extern void InitTimer(void);
