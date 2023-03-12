#include "pwm.h"


void pwm::Activate(const EN_ModuleId moduleId)
{ 
    // enable clock
    SYSCTL->RCGCPWM |= moduleId;
    
    // divided system clock as PWM source clock = 250 kHz
    SYSCTL->RCC |= (USEPWMDIV | PWMDIV_64);
    
    Disable(moduleId);
}


void pwm::Deactivate(const EN_ModuleId moduleId)
{
    Disable(moduleId);
    SYSCTL->RCGCPWM &= ~moduleId;
}

void pwm::Disable(const EN_ModuleId moduleId)
{
    pwm::Module module = GetModule(moduleId);
    module->ENABLE = 0;
}

pwm::Module pwm::GetModule(const EN_ModuleId moduleId)
{
    return (moduleId == E_Module0) ? PWM0 : PWM1;
}
  