#include "event_q.hpp"

void write_event(volatile event_q_t* queue, EV_E event){
    queue->fifo[queue->head++] = event;
}

uint8_t get_event(volatile event_q_t* queue, EV_E* out){
    while(queue->head == queue->tail){
        return 0;
    }

    *out = queue->fifo[queue->tail++];
    return 1;
}