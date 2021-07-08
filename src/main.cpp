#include <Arduino.h>
#include "general.h"

//---------ArcadeButtons-------------------
//---------ArcadeButtons_Leds--------------

#define LB_AB_L A0
#define RB_AB_L A1

#define LW_AB_L A2
#define RW_AB_L A3

#define LY_AB_L A4
#define RY_AB_L A5

#define LG_AB_L D3
#define RG_AB_L D2

//---------ArcadeButtons_Switches----------

#define LB_AB_S D12
#define RB_AB_S D11

#define LW_AB_S D10
#define RW_AB_S D9

#define LY_AB_S D8
#define RY_AB_S D7

#define LG_AB_S D6
#define RG_AB_S D5

//---------ArcadeButtons END---------------
//---------variable setup------------------

struct ArcadeSwitch
{
  const uint8_t m_LedPin;
  const uint8_t m_SwitchPin;
};

ArcadeSwitch Switches[] = 
{
  {LB_AB_L, LB_AB_S},
  {RB_AB_L, RB_AB_S},
  {LW_AB_L, LW_AB_S},
  {RW_AB_L, RW_AB_S},
  {LY_AB_L, LY_AB_S},
  {RY_AB_L, RY_AB_S},
  {LG_AB_L, LG_AB_S},
  {RG_AB_L, RG_AB_S}
};

uint8_t Button_Values = 0x0;
uint8_t Prev_Button_Values = 0x0;

//---------variable setup END--------------
//---------Forward declared functions------

void ButtonSetup();
void CheckForMultipleBits();

//---------Forward declared functions END--

void setup() {
  ButtonSetup();

  Serial.begin(9600);
}

void loop() {
  Button_Values = 0x0;

  for(int i = 0; i < 8; i++)
    Button_Values |= (digitalRead(Switches[i].m_SwitchPin) << i);

  CheckForMultipleBits();

  if(Button_Values != Prev_Button_Values && Button_Values != 0xFF)
  {
    Prev_Button_Values = Button_Values;
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(Switches[i].m_LedPin, (Button_Values & (1 << i)) ? LOW : HIGH);
    }
  }
  //Serial.println(Button_Values, BIN);
  delay(50);
}

void ButtonSetup()
{
  // --Leds------
  pinMode(Switches[0].m_LedPin, OUTPUT);
  pinMode(Switches[1].m_LedPin, OUTPUT);
  pinMode(Switches[2].m_LedPin, OUTPUT);
  pinMode(Switches[3].m_LedPin, OUTPUT);
  pinMode(Switches[4].m_LedPin, OUTPUT);
  pinMode(Switches[5].m_LedPin, OUTPUT);
  pinMode(Switches[6].m_LedPin, OUTPUT);
  pinMode(Switches[7].m_LedPin, OUTPUT);

  digitalWrite(Switches[0].m_LedPin, LOW);
  digitalWrite(Switches[1].m_LedPin, LOW);
  digitalWrite(Switches[2].m_LedPin, LOW);
  digitalWrite(Switches[3].m_LedPin, LOW);
  digitalWrite(Switches[4].m_LedPin, LOW);
  digitalWrite(Switches[5].m_LedPin, LOW);
  digitalWrite(Switches[6].m_LedPin, LOW);
  digitalWrite(Switches[7].m_LedPin, LOW);

  // --Switches--
  pinMode(Switches[0].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[1].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[2].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[3].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[4].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[5].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[6].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[7].m_SwitchPin, INPUT_PULLUP);
}

void CheckForMultipleBits()
{
  bool HasBeenSet = false;
  for(int i = 0; i < 8; i++)
  {
    if(!(Button_Values & (1 << i)) && HasBeenSet == false)
      HasBeenSet = true;
    else if(!(Button_Values & (1 << i)) && HasBeenSet == true)
      Button_Values |= (1 << i);
  }
}