#pragma once

#include <stdint.h>
#include "TM4C123GH6PM.h"


namespace
{
    using Register  = __IO uint32_t;
    
    constexpr uint32_t USEPWMDIV = (1U << 20);
    constexpr uint32_t PWMDIV_64 = (7U << 17);
}


namespace pwm
{
    using Module = PWM0_Type *;
    
    enum EN_ModuleId
    {
        E_Module0 = (1U << 0),
        E_Module1 = (1U << 1),
    };

    struct STRegisters
    {  
        Register * ctrl;
        Register * load;
        Register * comp;
        Register * gen;
        
        uint8_t channel;
        uint16_t gpioPctl;
    };

    void Activate(const EN_ModuleId moduleId);
    void Deactivate(const EN_ModuleId moduleId);
    
    void Disable(const EN_ModuleId moduleId);
    
    Module GetModule(const EN_ModuleId moduleId);
}
