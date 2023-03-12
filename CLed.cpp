#include <stdint.h>

#include "CLed.h"
#include "timer.h"


CLed::CLed(EN_Led colour, EN_BrightnessLevel initBrightness) :
    m_colour(colour),
    m_brightness(initBrightness),
    m_pwmInterface(pwm::E_Module1, this)
{
    if (!g_timerInit)
    {
        InitTimer();
    }
  
    // enable clock and AHB
    SYSCTL->RCGCGPIO    |= PORT_F;
	SYSCTL->GPIOHBCTL   |= PORT_F;
    
	// set LED GPIO to digital outputs
    GPIOF_AHB->DIR |= m_colour;
	GPIOF_AHB->DEN |= m_colour;
    
    // PWM
    GPIOF_AHB->AFSEL |= m_colour;    
    m_pwmInterface.SetInitValues();
}


CLed::~CLed()
{
    SwitchOff();

    // disable clock and AHB
    SYSCTL->RCGCGPIO    &= ~PORT_F;
    SYSCTL->GPIOHBCTL   &= ~PORT_F;

    // PWM
    m_pwmInterface.Deactivate();
}


/**
    Sets data bit of the LED.
*/
void CLed::SwitchOn() const
{
    // with PWM
    GPIOF_AHB->AFSEL |= m_colour; 
    SetBrightness(m_brightness);
    
    // without PWM
    //GPIOF_AHB->DATA_Bits[m_colour] = m_colour;
}


/**
    Unsets data bit of the LED.
*/
void CLed::SwitchOff() const
{
    GPIOF_AHB->AFSEL &= ~m_colour; 
    GPIOF_AHB->DATA_Bits[m_colour] = 0;
}


/**
    Toggles LED state between OFF and ON.
*/
void CLed::Toggle() const
{
    GPIOF_AHB->DATA_Bits[m_colour] ^= m_colour;
}


/**
    Sets the brightness of the LED to one of the predefined brightness levels.
*/
void CLed::SetBrightness(const EN_BrightnessLevel level) const
{
    m_pwmInterface.SetComp(level);
}


/**
    Sets the brightness of the LED to a discrete value.
*/
void CLed::SetBrightness(const uint16_t pwmCompValue) const
{
    m_pwmInterface.SetComp(pwmCompValue);
}


/**
    Returns the current brightness (PWM comp value) of the LED.
*/
Brightness CLed::GetBrightness() const
{
    return m_brightness;
}


/**
    Sets the LED to ON for one second, then OFF for one second.
*/
void CLed::BlinkOnce() const
{
    SwitchOn();
    DelayMilliseconds(1000);
    
    SwitchOff();
    DelayMilliseconds(1000);
}


/**
    Demo function that toggles between different LED brightness levels.
*/
void CLed::DemoDimming()
{    
    SwitchOn();
    
    SetBrightness(E_Led_Bright);
    DelayMilliseconds(2000);
    
    SetBrightness(E_Led_Mid);
    DelayMilliseconds(2000);
    
    SetBrightness(E_Led_Dim);
    DelayMilliseconds(2000);
}


/**
    Demo function that changes the LED brightness: dim -> bright -> dim.
*/
void CLed::DemoFading()
{
    SwitchOn();
  
    for(volatile Brightness i = E_Led_Dim; i > E_Led_Bright; i--)
    {
        SetBrightness(i);
        DelayMilliseconds(1);
    }
    DelayMilliseconds(100);
    
    for(volatile Brightness i = E_Led_Bright; i < E_Led_Dim; i++)
    {
        SetBrightness(i);
        DelayMilliseconds(1);
    }
    DelayMilliseconds(100);
}
