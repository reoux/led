#include "timer.h"

#include <assert.h>


extern uint16_t g_msCounter = 0U;
extern bool g_timerInit = false;


void InitTimer()
{
    SysTick->CTRL |= (ENABLE_SYSTICK | ENABLE_INTERRUPT | CLKSOURCE_4MHz);
    SysTick->LOAD = LOAD;
    
    g_timerInit = true;
}


void DelayMilliseconds(const uint16_t delay)
{
    assert(g_timerInit);
    
    g_msCounter = 0;
    while (delay > g_msCounter);
}


/**
    Interrupt handler for SysTick event.
*/
void SysTick_Handler()
{
    g_msCounter++;
}
