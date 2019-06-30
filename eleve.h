#include "state.h"

// HEADER POUR ELEVES
#ifndef ELEVE_H
#define ELEVE_H

struct Eleve
{
	char* eleve_name;
	enum{TRAVAIL, ATTEND, AVECTA} etat;
};

struct Eleve* Eleve_create(char* eleve_name);

void* Eleve_thread(void* info);

struct Eleve_thread_info {
    struct Eleve* eleve;
    struct state* state;
};


void Eleve_destroy( struct Eleve* self);

#endif
