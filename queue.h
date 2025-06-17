#ifndef QUEUE_H
#define QUEUE_h

typedef struct {
    char name[50]; 
    char type;     
} Client;

typedef struct {
    int max;    // tamanho alocado
    int size;   // número de elementos na fila
    int front;  // índice do primeiro elemento
    int rear;   // índice do último elemento
    Client** items; // vetor de ponteiros para Client (para armazenar clientes dinamicamente)
} t_queue;

t_queue* create_queue(int max);
int is_full(t_queue* queue);
int is_empty(t_queue* queue);
int size(t_queue* queue);
int enqueue(t_queue* queue, Client* client); 
Client* dequeue(t_queue* queue);           
Client* front_element(t_queue* queue);        
void destroy_queue(t_queue* queue);     

#endif