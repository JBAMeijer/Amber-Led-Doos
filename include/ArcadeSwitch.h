#ifndef __ARCADESWITCH__H
#define __ARCADESWITCH__H

#include <stdint.h>

struct ArcadeSwitch
{
  const uint8_t m_LedPin;
  const uint8_t m_SwitchPin;
};

#endif // __ARCADESWITCH__H