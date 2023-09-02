#include <Arduino.h>
#include "fsm.hpp"
#include "event_q.hpp"
#include "nokia_5510.hpp"
#include "snake.hpp"
#include "buttons.hpp"
#include "hardware.hpp"

void init(fsm_t* fsm, uint8_t event);
void line1(fsm_t* fsm, uint8_t event);
void line2(fsm_t* fsm, uint8_t event);
void snake(fsm_t* fsm, uint8_t event);

extern volatile buttonsdebounc buttons;

Nokia display(CLK, DIN, DC, CE, RST);

int main(void){

  pinMode(PinUp, INPUT);
  pinMode(PinDown, INPUT);
  pinMode(PinRight, INPUT);
  pinMode(PinLeft, INPUT);

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  OCR1AH = 0b01110101;
  OCR1AL = 0b00110000;
  TIMSK1 |= (1 << 1);
  SREG |= 1<<7;

  display.LCD_Init();
  display.LCD_Clear();

  EV_E event = ENTRY;
  fsm_t fsm;

  fsm_init(&fsm, &init);


  while(1){
    if(fsm_get_event(&event)){
      fsm_dispatch(&fsm, event);
    }
  }
  return 0;
}

void init(fsm_t* fsm, uint8_t event){
  switch(event){
    case EV_E::ENTRY:{
      char line1_txt[] = "LOADING";
      display.LCD_Clear();
      display.LCD_String(line1_txt, 20, 1, 2);
      _delay_ms(1000);
      fsm_transition(fsm, &line1);
      break;
    }
  }
}

void line1(fsm_t* fsm, uint8_t event){
  switch(event){
    case EV_E::ENTRY:{
      char line1_txt[] = "WELCOME";
      char line2_txt[] = "> SNAKE";
      char line3_txt[] = "  SETTINGS";
      char line4_txt[] = "0123";
      display.LCD_Clear();
      display.LCD_String(line1_txt, 20, 1, 2);
      display.LCD_String(line2_txt, 10, 3, 1);
      display.LCD_String(line3_txt, 10, 4, 1);
      display.LCD_Num(line4_txt, 20, 5);
      break;
    }
    case EV_E::BTN_DOWN_PRESSED:{
      fsm_transition(fsm, &line2);
      break;
    }
    case EV_E::BTN_RIGHT_PRESSED:{
      fsm_transition(fsm, &snake);
    }
  }
}

void line2(fsm_t* fsm, uint8_t event){
  switch(event){
    case EV_E::ENTRY:{
      char line1_txt[] = "WELCOME";
      char line2_txt[] = "  SNAKE";
      char line3_txt[] = "> SETTINGS";
      display.LCD_Clear();
      display.LCD_String(line1_txt, 20, 1, 2);
      display.LCD_String(line2_txt, 10, 3, 1);
      display.LCD_String(line3_txt, 10, 4, 1);
      break;
    }
    case EV_E::BTN_UP_PRESSED:{
      fsm_transition(fsm, &line1);
      break;
    }
  }
}

void snake(fsm_t* fsm, uint8_t event){
  switch(event){
    case EV_E::ENTRY:{
      buttons.SwitchUpstate = 0;
      buttons.SwitchDownState = 0;
      buttons.SwitchRightState = 0;
      buttons.SwitchLeftState = 0;
      snakeMain(display);
      display.LCD_Clear();
      fsm_transition(fsm, &init);
      break;
    }
  }
}