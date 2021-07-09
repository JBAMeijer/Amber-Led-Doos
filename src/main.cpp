#include <Arduino.h>
#include "general.h"

//---------Amber Leds----------------------

#define L_AL D6 // Left Amber Led
#define M_AL D5 // Middle Amber Led
#define R_AL D4 // Right Amber Led

//---------Amber Leds END------------------
//---------ArcadeButtons-------------------
//---------ArcadeButtons Leds--------------

#define LB_AB_L A0 // Left Blue ArcadeButton Led
#define RB_AB_L A1 // Right Blue ArcadeButton Led

#define LW_AB_L A2 // Left White ArcadeButton Led
#define RW_AB_L A3 // Right White ArcadeButton Led

#define LY_AB_L A4 // Left Yellow ArcadeButton Led
#define RY_AB_L A5 // Right Yellow ArcadeButton Led

//---------ArcadeButtons Switches----------

#define LB_AB_S D12 // Left Blue ArcadeButton Switch
#define RB_AB_S D11 // Right Blue ArcadeButton Switch

#define LW_AB_S D10 // Left White ArcadeButton Switch
#define RW_AB_S D9  // Right White ArcadeButton Switch

#define LY_AB_S D8  // Left Yellow ArcadeButton Switch
#define RY_AB_S D7  // Right Yellow ArcadeButton Switch

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
  {RY_AB_L, RY_AB_S}
};

uint8_t Button_Values = 0x0;
uint8_t Prev_Button_Values = 0x0;

const uint8_t Amount_Of_Switches = sizeof(Switches) / sizeof(ArcadeSwitch);

//---------variable setup END--------------
//---------Forward declared functions------

void AmberLedSetup();
void ButtonSetup();
void CheckForMultipleBits();

//---------Forward declared functions END--

void setup() {
  AmberLedSetup();
  ButtonSetup();
  Serial.begin(9600);
}

void loop() {
  Button_Values = 0x0;

  for(int i = 0; i < Amount_Of_Switches; i++)
    Button_Values |= (digitalRead(Switches[i].m_SwitchPin) << i);

  CheckForMultipleBits();

  if(Button_Values != Prev_Button_Values && Button_Values != 0x3F)
  {
    Prev_Button_Values = Button_Values;
    for(int i = 0; i < Amount_Of_Switches; i++)
    {
      digitalWrite(Switches[i].m_LedPin, (Button_Values & (1 << i)) ? LOW : HIGH);
    }
  }
  //Serial.println(Button_Values, BIN);
  delay(50);
}

void AmberLedSetup()
{
  pinMode(L_AL, OUTPUT);
  pinMode(M_AL, OUTPUT);
  pinMode(R_AL, OUTPUT);

  digitalWrite(L_AL, LOW);
  digitalWrite(M_AL, LOW);
  digitalWrite(R_AL, LOW);
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


  digitalWrite(Switches[0].m_LedPin, LOW);
  digitalWrite(Switches[1].m_LedPin, LOW);
  digitalWrite(Switches[2].m_LedPin, LOW);
  digitalWrite(Switches[3].m_LedPin, LOW);
  digitalWrite(Switches[4].m_LedPin, LOW);
  digitalWrite(Switches[5].m_LedPin, LOW);

  // --Switches--
  pinMode(Switches[0].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[1].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[2].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[3].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[4].m_SwitchPin, INPUT_PULLUP);
  pinMode(Switches[5].m_SwitchPin, INPUT_PULLUP);
}

void CheckForMultipleBits()
{
  bool HasBeenSet = false;
  for(int i = 0; i < Amount_Of_Switches; i++)
  {
    if(!(Button_Values & (1 << i)) && HasBeenSet == false)
      HasBeenSet = true;
    else if(!(Button_Values & (1 << i)) && HasBeenSet == true)
      Button_Values |= (1 << i);
  }
}