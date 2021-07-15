#ifndef __AMBERLEDS__H
#define __AMBERLEDS__H

enum LightOption
{
    SET_ALL_LIGHTS_ON = 0,
    SET_ALL_LIGHTS_OFF,
    SET_LIGHT_OPTION_1,
    SET_LIGHT_OPTION_2,
    SET_LIGHT_OPTION_3,

    NONE = 255
};

void SetAllOn();
void SetAllOff();
void SetLightOption1();
void SetLightOption2();
void SetLightOption3();

#endif // __AMBERLEDS__H