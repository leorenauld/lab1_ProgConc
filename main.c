#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10
#define M 3

int* vetor;
int* vetorTeste;

void criarVetor() {
    vetor = (int*)malloc(N*sizeof(int));
    vetorTeste = (int*)malloc(N*sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int aux = rand() % 10 + 1;
        vetor[i] = aux;
        vetorTeste[i] = aux;
    }
}

void *ao_quadrado(void *arg) {
    int inicio = * (int *) arg;
    for (int j = 0; j < N/M + 1; j++) {
        if (inicio + j < N){
            vetor[inicio + j] *= vetor[inicio + j];
        }
    }
    pthread_exit(NULL);
}

void printVetor(int *vetor, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void testeVetor() {
    for (int i = 0; i < N; i++) {
        vetorTeste[i] *= vetorTeste[i];
    }
    printf("Vetor Teste: ");
    printVetor(vetorTeste, 10);
    int igual = 1;
    for (int i = 0; i < N; i++) {
        if (vetorTeste[i] != vetor[i]) {
            igual = 0;
        }
    }
    if (igual) {
        printf("O vetor final está correto.");
    }
    else {
        printf("O vetor final está errado.");
    }
}

int main(void)
{
    criarVetor();
    printf("Vetor inicial: ");
    printVetor(vetor, 10);
    int d = N/M;
    pthread_t tid[N];
    int ident[M];
    for (int i = 0; i < M; i++) {
        ident[i] = i * (d + 1);
        if (pthread_create(&tid[i], NULL, ao_quadrado, (void *)&ident[i]))
            printf("Erro");
    }
    for (int i = 0; i < M; i++) {
        if (pthread_join(tid[i], NULL))
            printf("Erro");
    }
    printf("Vetor final: ");
    printVetor(vetor, 10);
    testeVetor();
    return 0;
}
