#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "queue.h"
#include "state.h"
#include "eleve.h"
#include "ta.h"

/*------------------------------------------------------------
Fichier: main.c

Nom: Valentin Magot
Numero d'etudiant: 8843488

Description: Ce programme fournie la logique du project



-------------------------------------------------------------*/

//enleve la memoire
void clean_memory(int code, struct state* state, pthread_t* threads) {
    State_destroy(state); 

    if(threads) {
        free(threads);
    }

    exit(code);
}

int main(int argc, char* argv[]) {
    //verifie argument
    if(argc < 2) {
        fprintf(stderr, "Enter le nom d'au moin un etudiant.\n");

        clean_memory(1, NULL, NULL);
    }

    //nombre  eleves
    int num_eleve = argc - 1;

    struct state* state = State_create();
    state->queue = createQueue();
    state->eleve = (struct Eleve**)malloc((num_eleve) * sizeof(struct Eleve*));
    state->num_eleve = num_eleve;
    state->ta = Ta_create();

    // ajoute les etudiants
    for(int i = 0; i < num_eleve; ++i) {
        state->eleve[i] = Eleve_create(argv[i + 1]);
    }

    // commence le ta qui va dormir
    pthread_t ta_thread;
    int result = pthread_create(&ta_thread, NULL, Ta_thread, (void*)state);
    if(result != 0) {
        fprintf(stderr, "Error creating a thread for the TA.\n");
        clean_memory(1, state, NULL);
    }

    // Commence les etudiants
    pthread_t* eleve_threads = (pthread_t*)malloc((num_eleve) * sizeof(pthread_t));

    for(int i = 0; i < num_eleve; ++i) {
        struct Eleve_thread_info* info = (struct Eleve_thread_info*)malloc(sizeof(struct Eleve_thread_info));
        info->eleve = state->eleve[i];
        info->state = state;

        
        result = pthread_create(eleve_threads + i, NULL, Eleve_thread, (void*)argv);
        if(result != 0) {
            fprintf(stderr, "Error creating a thread for student %s.\n", state->eleve[i]->eleve_name);
            clean_memory(1, state, eleve_threads);
        }
    }

    // join ta threads
    pthread_join(ta_thread, NULL);

    // join student threads
    for(int i = 0; i < num_eleve; ++i) {
        pthread_join(eleve_threads[i], NULL);
    }

    clean_memory(0, state, eleve_threads);

    return 0;
}
