#include "fsm.hpp"

static volatile event_q_t event_q;

void fsm_add_event(EV_E event){
    write_event(&event_q, event);
}

uint8_t fsm_get_event(EV_E* out){
    return get_event(&event_q, out);
}

void fsm_init(fsm_t* fsm, state_fp init_state){
    fsm->state = init_state;
    fsm_dispatch(fsm, EV_E::ENTRY);
}

void fsm_dispatch(fsm_t* fsm, uint8_t event){
    (*(fsm)->state)(fsm, event);
}

void fsm_transition(fsm_t* fsm, state_fp new_state){
    fsm_dispatch(fsm, EV_E::EXIT);
    fsm->state = new_state;
    fsm_dispatch(fsm, EV_E::ENTRY);
}