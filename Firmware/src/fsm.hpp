#ifndef FSM_H_
#define FSM_H_

#include <stdint.h>
#include "event_q.hpp"

typedef struct fsm_t fsm_t;

typedef void(*state_fp)(fsm_t* fsm, uint8_t event);

struct fsm_t{
    state_fp state;
};

void fsm_init(fsm_t* fsm, state_fp init_state);
void fsm_dispatch(fsm_t* fsm, uint8_t event);
void fsm_transition(fsm_t* fsm, state_fp new_state);
void fsm_add_event(EV_E event);
uint8_t fsm_get_event(EV_E* out);

#endif