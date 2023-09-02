#ifndef EVENT_Q_H
#define EVENT_Q_H

#include <stdint.h>

typedef enum{
    ENTRY,
    EXIT,
    LINE1,
    LINE2,
    BTN_UP_PRESSED,
    BTN_DOWN_PRESSED,
    BTN_RIGHT_PRESSED,
}EV_E;

typedef struct{
    EV_E fifo[32];
    uint8_t head :5;
    uint8_t tail :5;
}event_q_t;

void write_event(volatile event_q_t* queue, EV_E event);
uint8_t get_event(volatile event_q_t* queue, EV_E* out);


#endif