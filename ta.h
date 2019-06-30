// HEADER POUR TA
#ifndef TA_H
#define TA_H

#include <semaphore.h>

#include "state.h"
#include "eleve.h"

struct Ta
{
	struct Eleve* eleve;
	enum{DORS, AIDE} etat;
	sem_t semaphore;
};

struct Ta* Ta_create();

void* Ta_thread(void* arg);

void Ta_destroy( struct Ta* self);


#endif
