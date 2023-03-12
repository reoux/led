#include "CPwmLedInterface.h"
#include "CLed.h"


CPwmLedInterface::CPwmLedInterface(const pwm::EN_ModuleId moduleId, const CLed * led) :
    m_pwmModuleId(moduleId),
    m_pwmModule(pwm::GetModule(moduleId)),
    m_led(led)
{
    pwm::Activate(moduleId);
    ConfigureRegisters(led);
}


CPwmLedInterface::~CPwmLedInterface()
{
    Deactivate();
}


void CPwmLedInterface::SetInitValues() const
{ 
    const uint8_t genCompOffset = (m_led->m_colour == E_Led_BLUE) ? 0U : 4U;
    
    // disable before configuring
    *(m_pwmRegisters.ctrl) &= ~(1U << 0); 
    
    *(m_pwmRegisters.ctrl) &= ~(1U << 1);                   // mode: down-counting
    *(m_pwmRegisters.gen)  |= (0x3 << 2);                   // PWM high when counter == load
    *(m_pwmRegisters.gen)  |= (0x2 << 6) << genCompOffset;  // PWM low  when counter == comp 
    *(m_pwmRegisters.load)  = LOAD;
    *(m_pwmRegisters.comp)  = m_led->GetBrightness();    
    
    // re-enable
    SYSCTL->SRPWM           &= ~m_pwmModuleId;
    GPIOF_AHB->PCTL         |= m_pwmRegisters.gpioPctl; 
    m_pwmModule->ENABLE     |= m_pwmRegisters.channel;
    *(m_pwmRegisters.ctrl)  |= (1U << 0);
}


void CPwmLedInterface::Deactivate() const
{
  pwm::Deactivate(m_pwmModuleId);
}
        

void CPwmLedInterface::SetComp(const int val) const
{
    *m_pwmRegisters.comp = val;
}


void CPwmLedInterface::ConfigureRegisters(const CLed * led) const
{
    switch (led->m_colour)
    {
        case E_Led_RED:
            m_pwmRegisters.ctrl = &(m_pwmModule->_2_CTL);
            m_pwmRegisters.load = &(m_pwmModule->_2_LOAD);
            m_pwmRegisters.gen  = &(m_pwmModule->_2_GENB);
            m_pwmRegisters.comp = &(m_pwmModule->_2_CMPB);
            
            m_pwmRegisters.channel  = E_PwmCh_RED;
            m_pwmRegisters.gpioPctl = E_PortControl_RED;
            
            break;
            
        case E_Led_BLUE:
            m_pwmRegisters.ctrl = &(m_pwmModule->_3_CTL);
            m_pwmRegisters.load = &(m_pwmModule->_3_LOAD);
            m_pwmRegisters.gen  = &(m_pwmModule->_3_GENA);
            m_pwmRegisters.comp = &(m_pwmModule->_3_CMPA);
            
            m_pwmRegisters.channel  = E_PwmCh_BLUE;
            m_pwmRegisters.gpioPctl = E_PortControl_BLUE;
    
            break;
            
        case E_Led_GREEN:
            m_pwmRegisters.ctrl = &(m_pwmModule->_3_CTL);
            m_pwmRegisters.load = &(m_pwmModule->_3_LOAD);
            m_pwmRegisters.gen  = &(m_pwmModule->_3_GENB);
            m_pwmRegisters.comp = &(m_pwmModule->_3_CMPB);
            
            m_pwmRegisters.channel  = E_PwmCh_GREEN;
            m_pwmRegisters.gpioPctl = E_PortControl_GREEN;
    
            break;
            
        default:
          break;
    }
}

