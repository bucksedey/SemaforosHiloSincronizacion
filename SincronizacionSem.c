/*
Grupo: 4CV1
Flores Anzurez Marco Antonio

En este ejemplo, dos procesos incrementan una variable común, sharedVariable. Usamos un semáforo para garantizar 
que los procesos no accedan a la variable al mismo tiempo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex; // Declaración del semáforo
int sharedVariable = 0;

void *incrementVariable(void *arg) {
    sem_wait(&mutex); // Espera al semáforo (decrementa el valor del semáforo)
    sharedVariable++; // Incrementa la variable compartida
    printf("Valor de la variable compartida después del incremento: %d\n", sharedVariable);
    sem_post(&mutex); // Libera el semáforo (incrementa el valor del semáforo)
}

int main() {
    pthread_t t1, t2;
    sem_init(&mutex, 0, 1); // Inicialización del semáforo con valor inicial 1

    pthread_create(&t1, NULL, incrementVariable, NULL); // Crea el hilo t1
    pthread_create(&t2, NULL, incrementVariable, NULL); // Crea el hilo t2
    
    pthread_join(t1, NULL); // Espera a que el hilo t1 termine
    pthread_join(t2, NULL); // Espera a que el hilo t2 termine
    
    sem_destroy(&mutex); // Destruye el semáforo

    return 0;
}
