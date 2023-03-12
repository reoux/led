#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "TM4C123GH6PM.h"


extern uint16_t g_msCounter;
extern bool g_timerInit;

constexpr uint8_t ENABLE_SYSTICK    = (1U << 0);
constexpr uint8_t ENABLE_INTERRUPT  = (1U << 1);
constexpr uint8_t CLKSOURCE_4MHz    = (0U << 2);

// LOAD = T_timer / T_clock = (1 ms) / (0.25 microseconds) - 1
// -1 to account for counting from zero
constexpr uint16_t LOAD = 4000 - 1;


void InitTimer(void);
void DelayMilliseconds(const uint16_t delay);