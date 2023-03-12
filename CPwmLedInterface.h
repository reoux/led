#pragma once

#include "IPwm.h"


#define AFSEL_PWM_FUNCTION  (5U)

namespace
{    
    // LOAD = f_clock / f_PWM = (250 kHz) / (50 Hz)
    static constexpr uint32_t LOAD = 5000U;
    
    enum EN_PortControl : uint16_t
    {
        E_PortControl_RED   = (AFSEL_PWM_FUNCTION << 4),
        E_PortControl_BLUE  = (AFSEL_PWM_FUNCTION << 8),
        E_PortControl_GREEN = (AFSEL_PWM_FUNCTION << 12),
    };
    
    enum EN_PwmChannel : uint8_t
    {
        E_PwmCh_RED   = (1U << 5), // RED:   M1PWM5 (Generator 2 Signal B)
        E_PwmCh_BLUE  = (1U << 6), // BLUE:  M1PWM6 (Generator 3 Signal A)
        E_PwmCh_GREEN = (1U << 7), // GREEN: M1PWM7 (Generator 3 Signal B)
    };
}

class CLed;

class CPwmLedInterface : public IPwm<CLed>
{
    public:
        CPwmLedInterface(const pwm::EN_ModuleId moduleId, const CLed * led);  
        ~CPwmLedInterface() override;

        void SetInitValues() const override;
        void SetComp(const int val) const override;
        void Deactivate() const override;        
      
    private:
        void ConfigureRegisters(const CLed * led) const override final;

        mutable pwm::STRegisters m_pwmRegisters;
        const pwm::EN_ModuleId m_pwmModuleId;
        const pwm::Module m_pwmModule;
        const CLed * m_led;
};
