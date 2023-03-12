#pragma once

#include "TM4C123GH6PM.h"
#include "CPwmLedInterface.h"

#define PORT_F 		        (1U << 5)

enum EN_Led : uint8_t
{
    E_Led_RED   = (1U << 1),
    E_Led_BLUE  = (1U << 2),
    E_Led_GREEN = (1U << 3),
    E_Led_ALL   = (E_Led_RED | E_Led_BLUE | E_Led_GREEN),
};


using Brightness = uint16_t;
enum EN_BrightnessLevel : Brightness // PWM Comp value
{
    E_Led_Dim    = LOAD - 1U, // 5000U - 1U
    E_Led_Mid    = 3000U,
    E_Led_Bright = 1000U,
};


class CLed
{
    public:
        CLed(EN_Led colour, EN_BrightnessLevel initBrightness = E_Led_Dim);
        ~CLed();
        
        void SwitchOn() const;
        void SwitchOff() const;
        void Toggle() const;
        
        void SetBrightness(const EN_BrightnessLevel level) const;
        void SetBrightness(const uint16_t pwmCompValue) const;
        Brightness GetBrightness() const;
        
        void BlinkOnce() const;
        void DemoDimming();
        void DemoFading();
        
        const EN_Led m_colour;
        
    private:      
        CPwmLedInterface m_pwmInterface;
        mutable Brightness m_brightness;
};
