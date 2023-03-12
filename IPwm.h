#pragma once

#include "pwm.h"

template<typename T>
class IPwm
{
    public:
        IPwm() {};        
        virtual ~IPwm() = 0;
  
        /** Sets the [initial] values of the PWM module registers. */
        virtual void SetInitValues() const = 0;
        /** Sets the value of the PWM comp register. */
        virtual void SetComp(const int val) const = 0;
        virtual void Deactivate() const = 0;
        
        
    protected:
        /** Sets the addresses of the required PWM module. */
        virtual void ConfigureRegisters(const T * obj) const = 0;
};


template<typename T>
inline IPwm<T>::~IPwm() {}
