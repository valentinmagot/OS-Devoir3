#include "ta.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "state.h"
#include "eleve.h"
#include <unistd.h>

//Constuctor
void Ta_init(struct Ta* self){
	self->eleve = NULL;
	self->etat = DORS;
}

// Constructor + Allocation (new)
struct Ta* Ta_create(){
	struct Ta* new_Ta = (struct Ta*)malloc(sizeof(struct Ta));
	Ta_init(new_Ta);
	sem_init(&new_Ta->semaphore, 0, 0);
	return new_Ta;
}

void Ta_travail(struct state* state) {
    struct Ta* self = state->ta;

    // master loop
    while(1) {
        // awake
        sem_wait(&self->semaphore);
        printf("Le Ta se reveil.\n");

        // process all students
        struct Eleve* eleve;
        while( (eleve = dequeue(state->queue)) ) {
            eleve->etat = AVECTA;
            printf("Le Ta aide %s dans le bureau.\n", eleve->eleve_name);
            sleep(rand() % 16 + 4);
            eleve->etat = TRAVAIL;
        }

        // go to sleep
        // sem stays locked until a student unlocks it
        printf("Le ta se rendors\n");
        self->etat = DORS;
    }

    printf("Tutoring done");
}

//Ta thread
void* Ta_thread(void* state) {
    struct state* s = (struct state*)state;
    Ta_travail(s);

    return NULL;
}

// Destructor
void Ta_reset( struct Ta* self){
}

//Destructor with dellocation
void Ta_destroy( struct Ta* self){
	if (self) {
		Ta_reset(self);
		sem_destroy(&self->semaphore);
		free(self);
	}
}
