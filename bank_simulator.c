#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcpy
#include "queue.h"  // Nosso TAD Fila

#define MAX_QUEUE_CAPACITY 100

int prioridade_consecutiva_count = 0;

Client** atendidos_list = NULL;
int atendidos_count = 0;
int atendidos_capacity = 10;

void add_to_atendidos_list(Client* client) {
    if (atendidos_list == NULL) {
        atendidos_list = (Client**)malloc(sizeof(Client*) * atendidos_capacity);
        if (atendidos_list == NULL) {
            perror("Erro ao alocar lista de atendidos");
            exit(EXIT_FAILURE);
        }
    } else if (atendidos_count >= atendidos_capacity) {
        atendidos_capacity *= 2;
        atendidos_list = (Client**)realloc(atendidos_list, sizeof(Client*) * atendidos_capacity);
        if (atendidos_list == NULL) {
            perror("Erro ao realocar lista de atendidos");
            exit(EXIT_FAILURE);
        }
    }
    atendidos_list[atendidos_count++] = client;
}

void atender_caixa(t_queue* general_queue, t_queue* priority_queue) {
    Client* served_client = NULL;

    if (!is_empty(priority_queue) && prioridade_consecutiva_count < 3) {
        served_client = dequeue(priority_queue);
        if (served_client != NULL) {
            prioridade_consecutiva_count++;
            printf("Atendido prioritario: %s\n", served_client->name); // Mensagem de atendimento
        }
    } else if (!is_empty(general_queue)) {
        served_client = dequeue(general_queue);
        if (served_client != NULL) {
            prioridade_consecutiva_count = 0;
            printf("Atendido geral: %s\n", served_client->name); // Mensagem de atendimento
        }
    } else if (!is_empty(priority_queue) && prioridade_consecutiva_count >= 3) {
        fprintf(stderr, "Atenção: Fila de prioridade tem clientes, mas atingiu limite de 3 consecutivos. Fila geral vazia. Nenhum cliente atendido neste momento.\n");
    } else {
        printf("Ambas as filas estao vazias. Nenhum cliente para atender.\n"); // Mensagem para filas vazias
    }

    if (served_client != NULL) {
        add_to_atendidos_list(served_client);
    }
}

int main() {
    t_queue* general_queue = create_queue(MAX_QUEUE_CAPACITY);
    t_queue* priority_queue = create_queue(MAX_QUEUE_CAPACITY);

    char command_type;
    char client_name[50];

    printf("Simulador de Fila do Banco\n");
    printf("Comandos: 'g NOME' (geral), 'p NOME' (prioritario), 's' (servir), 'f' (finalizar expediente)\n");
    printf("Entre com o comando: \n"); 

    while (scanf(" %c", &command_type) == 1) {
        if (command_type == 'g' || command_type == 'p') {
            scanf("%s", client_name);

            Client* new_client = (Client*)malloc(sizeof(Client));
            if (new_client == NULL) {
                perror("Erro ao alocar novo cliente");
                exit(EXIT_FAILURE);
            }
            strcpy(new_client->name, client_name);
            new_client->type = command_type;

            if (command_type == 'g') {
                if(enqueue(general_queue, new_client)) {
                    printf("Cliente geral '%s' adicionado a fila geral.\n", new_client->name);
                } else {
                    free(new_client); 
                }
            } else { 
                if(enqueue(priority_queue, new_client)) {
                    printf("Cliente prioritario '%s' adicionado a fila de prioridade.\n", new_client->name);
                } else {
                    free(new_client); 
                }
            }
        } else if (command_type == 's') {
            printf("Comando 's' recebido. Tentando atender cliente...\n");
            atender_caixa(general_queue, priority_queue);
        } else if (command_type == 'f') {
            printf("Comando 'f' recebido. Finalizando expediente...\n");

            Client* client_to_serve_at_end = NULL; 
            while (!is_empty(priority_queue) || !is_empty(general_queue)) {
                if (!is_empty(priority_queue)) {
                    client_to_serve_at_end = dequeue(priority_queue);
                    printf("Atendido (final expediente) prioritario: %s\n", client_to_serve_at_end->name);
                } else if (!is_empty(general_queue)) {
                    client_to_serve_at_end = dequeue(general_queue);
                    printf("Atendido (final expediente) geral: %s\n", client_to_serve_at_end->name);
                }

                if (client_to_serve_at_end != NULL) {
                    add_to_atendidos_list(client_to_serve_at_end);
                    if (client_to_serve_at_end->type == 'g') {
                        prioridade_consecutiva_count = 0;
                    } else {
                        prioridade_consecutiva_count++;
                    }
                }
            }

            printf("\n--- Clientes Atendidos no Expediente ---\n");
            for (int i = 0; i < atendidos_count; i++) {
                printf("%s%s", atendidos_list[i]->name, (i == atendidos_count - 1) ? "" : ", ");
            }
            printf("\n");
            printf("--- Fim do Expediente ---\n");

            for(int i=0; i<atendidos_count; i++){
                free(atendidos_list[i]);
            }
            free(atendidos_list);
            atendidos_list = NULL;
            atendidos_count = 0;
            atendidos_capacity = 10;
            prioridade_consecutiva_count = 0; 

            break; 
        } else {
            printf("Comando invalido. Use 'g NOME', 'p NOME', 's', ou 'f'.\n");
        }
        printf("Entre com o proximo comando: \n"); 
    }

    destroy_queue(general_queue);
    destroy_queue(priority_queue);

    return EXIT_SUCCESS;
}