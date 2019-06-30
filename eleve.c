#include "eleve.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "state.h"

/*------------------------------------------------------------
Fichier: eleve.c

Nom: Valentin Magot
Numero d'etudiant: 8843488

Description: Ce programme la classe eleve



-------------------------------------------------------------*/

//Constuctor
void Eleve_init(struct Eleve* self, char* eleve_name){
	self->eleve_name = eleve_name;
	self->etat = TRAVAIL;
}

// Constructor + Allocation (new)
struct Eleve* Eleve_create(char* name){
	struct Eleve* new_eleve = (struct Eleve*)malloc(sizeof(struct Eleve));
	Eleve_init(new_eleve, name);
	return new_eleve;
}

void Eleve_travail(struct Eleve* self, struct state* state) {

    while(1) {
        if(self->etat == TRAVAIL) {
            printf("%s travail.\n", self->eleve_name);

            // work for a bit
            sleep(rand() % 64 + 16);

            // try to get into the queue
            printf("%s a besoin d'aide et va voir au bureau du TA.\n", self->eleve_name);
            if(enqueue(state->queue, self)) {
                self->etat = ATTEND;
            }
            else {
                printf(" %s ne peut pas se mettre en ligne : La file est pleinne.\n", self->eleve_name);
            }
        }

        else if(self->etat == ATTEND) {
            if(head(state->queue) == self && state->ta->etat == DORS) {
                // wake the lazy ass up
                printf("Le Ta dors;  %s reveil le Ta.\n", self->eleve_name);
                state->ta->etat = AIDE;
                sem_post(&state->ta->semaphore);
            }

            sleep(1);
        }

        // no action if CONSULTING, the TA thread takes care of it
    }
}

void* Eleve_thread(void* info) {
	struct Eleve_thread_info* i = (struct Eleve_thread_info*)info;
    Eleve_travail(i->eleve, i->state);

    free(i);
    return NULL;
}

// Destructor
void Eleve_reset( struct Eleve* self){
}

//Destructor with dellocation
void Eleve_destroy( struct Eleve* self){
	if (self) {
		Eleve_reset(self);
		free(self);
	}
}
