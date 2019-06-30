// C program for array implementation of queue 
#include "queue.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#include "eleve.h"

/*------------------------------------------------------------
Fichier: queue.c

Nom: Valentin Magot
Numero d'etudiant: 8843488

Description: Ce programme fournie une implementation d'une file.



-------------------------------------------------------------*/

//Constuctor
void Queue_init(struct Queue* self){
	self->head = self->size = 0;
	self->tail = 0;
} 

// function to create a queue  
struct Queue* createQueue() 
{ 
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
	Queue_init(queue);
	pthread_mutex_init(&queue->mutex, NULL);

	return queue; 
} 

int isFull(struct Queue* self) 
{  return (self->size == 10);  }

int isEmpty(struct Queue* self) 
{  return (self->size == 0); } 

// Function to add an item to the queue. 
// It changes tail and size 
int enqueue(struct Queue* self, struct Eleve* eleve) 
{ 
	if (isFull(self)) 
		return 0;
	self->tail = (self->tail + 1)%10; 
	self->list[self->tail] = eleve; 
	self->size = self->size + 1; 
	

	pthread_mutex_unlock(&self->mutex);
	return 1;
} 

// Function to remove an item from queue. 
// It changes head and size 
struct Eleve* dequeue(struct Queue* self) 
{ 
	if (isEmpty(self)) 
		return 0; 
	struct Eleve* item = self->list[self->head]; 
	self->head = (self->head + 1)%10; 
	self->size = self->size - 1; 
	return item; 
} 

// Function to get front of queue 
struct Eleve* head(struct Queue* self) 
{ 
	if (isEmpty(self)) 
		return 0; 
	return self->list[self->head]; 
} 

// Function to get rear of queue 
struct Eleve* tail(struct Queue* self) 
{ 
	if (isEmpty(self)) 
		return 0; 
	return self->list[self->tail]; 
} 

void Queue_destroy(struct Queue* self) {
	if(self) {
        free(self->list);
        pthread_mutex_destroy(&self->mutex);
        free(self);
    }
}
