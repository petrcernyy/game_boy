#include "buttons.hpp"
#include "hardware.hpp"
#include "fsm.hpp"

volatile buttonsdebounc buttons = {0};

ISR (TIMER1_COMPA_vect)
{
  buttons.SwitchUpConn <<= 1;
  buttons.SwitchUpConn |= digitalRead(PinUp);
  buttons.SwitchDownConn <<= 1;
  buttons.SwitchDownConn |= digitalRead(PinDown);
  buttons.SwitchRightConn <<= 1;
  buttons.SwitchRightConn |= digitalRead(PinRight);
  buttons.SwitchLeftConn <<= 1;
  buttons.SwitchLeftConn |= digitalRead(PinLeft);

  if(buttons.SwitchUpConn == RISING_EDGE){
    fsm_add_event(EV_E::BTN_UP_PRESSED);
    buttons.SwitchUpstate = 1;
    buttons.SwitchDownState = 0;
    buttons.SwitchRightState = 0;
    buttons.SwitchLeftState = 0;
  }
  if(buttons.SwitchDownConn == RISING_EDGE){
    fsm_add_event(EV_E::BTN_DOWN_PRESSED);
    buttons.SwitchUpstate = 0;
    buttons.SwitchDownState = 1;
    buttons.SwitchRightState = 0;
    buttons.SwitchLeftState = 0;
  }
  if(buttons.SwitchRightConn == RISING_EDGE){
    fsm_add_event(EV_E::BTN_RIGHT_PRESSED);
    buttons.SwitchUpstate = 0;
    buttons.SwitchDownState = 0;
    buttons.SwitchRightState = 1;
    buttons.SwitchLeftState = 0;
  }
  if(buttons.SwitchLeftConn == RISING_EDGE){
    buttons.SwitchUpstate = 0;
    buttons.SwitchDownState = 0;
    buttons.SwitchRightState = 0;
    buttons.SwitchLeftState = 1;
  }

}