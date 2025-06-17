#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "queue.h"

t_queue* create_queue(int max){
    t_queue* queue = (t_queue*)malloc(sizeof(t_queue));
    if (queue == NULL) {
        perror("Erro ao alocar memória para a estrutura da fila");
        exit(EXIT_FAILURE);
    }
    queue->max = max;
    queue->size = 0;
    queue->front = 0; 
    queue->rear = 0;  

    queue->items = (Client**)malloc(sizeof(Client*) * max);
    if (queue->items == NULL) {
        perror("Erro ao alocar memória para os itens da fila");
        free(queue); 
        exit(EXIT_FAILURE);
    }
    return queue;
}

int is_full(t_queue* queue){
    return queue->size == queue->max;
}

int is_empty(t_queue* queue){
    return queue->size == 0;
}

int size(t_queue* queue){
    return queue->size;
}

int enqueue(t_queue* queue, Client* client){
    if (is_full(queue)) {
        fprintf(stderr, "Erro: Fila cheia. Não é possível enfileirar.\n");
        return 0; 
    }

    queue->items[queue->rear] = client; 
    queue->rear = (queue->rear + 1) % queue->max; 
    queue->size++; 
    return 1; 
}

Client* dequeue(t_queue* queue){
    if (is_empty(queue)) {
        fprintf(stderr, "Erro: Fila vazia. Não é possível desenfileirar.\n");
        return NULL; 
    }

    Client* dequeued_client = queue->items[queue->front]; 
    queue->front = (queue->front + 1) % queue->max;
    queue->size--; 
    return dequeued_client; 
}

Client* front_element(t_queue* queue){
    if (is_empty(queue)) {
        return NULL; 
    }
    return queue->items[queue->front]; 
}

void destroy_queue(t_queue* queue){
    if (queue == NULL) return;
    free(queue->items); 
    free(queue);        
}
