#include "state.h"

#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "queue.h"
#include "eleve.h"
#include "ta.h"

/*------------------------------------------------------------
Fichier: state.c

Nom: Valentin Magot
Numero d'etudiant: 8843488

Description: Ce programme l'etat du TA 



-------------------------------------------------------------*/


struct state* State_create() {
    struct state* new_state = (struct state*)malloc(sizeof(struct state));
    memset(new_state, 0, sizeof(struct state));
    return new_state;
}

void State_destroy(struct state* self) {
    if(self) {
        Ta_destroy(self->ta);
        Queue_destroy(self->queue);

        if(self->eleve) {
            for(int i = 0; i < self->num_eleve; ++i) {
                Eleve_destroy(self->eleve[i]);
            }
            free(self->eleve);
        }

        free(self);
    }
}
