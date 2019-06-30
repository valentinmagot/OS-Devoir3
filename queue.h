#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

#include "eleve.h"


struct Queue {
    struct Eleve* list[10];
    int head, tail, size;
    pthread_mutex_t mutex;
};

struct Queue* createQueue();

int enqueue(struct Queue* self, struct Eleve* eleve);

struct Eleve* dequeue(struct Queue* self);

struct Eleve* head(struct Queue* self);

struct Eleve* tail(struct Queue* self);

void Queue_destroy(struct Queue* self);

#endif