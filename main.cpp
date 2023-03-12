#include "CLed.h"


int main()
{    
    CLed led(E_Led_RED);
    led.BlinkOnce();
    led.DemoDimming();
    led.DemoFading();
	return 0;
}