#ifndef STATE_H
#define STATE_H

#include "queue.h"
#include "eleve.h"
#include "ta.h"

struct state {
    struct Queue* queue;
    struct Ta* ta;
    struct Eleve** eleve;
    int num_eleve;
};

struct state* State_create();

void State_destroy(struct state* self);

#endif