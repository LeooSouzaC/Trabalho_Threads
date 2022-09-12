//Nome: Leonardo Souza de Carvalho;
//Disciplina: Sistemas Operacionais;
//Tipo: SingleThread
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

pthread_t thread_1;
pthread_t thread_2;

//Matrizes Matriciais:
int a[3][3] = { 1,2,0,
                1,5,4,
                2,6,9};
int b[3][3] = { 8,7,6,
                2,3,7,
                4,7,2};
int c[3][3];

//Matrizes Posicionais:
int d[3][3] = {2,3,0,
                4,5,3,
                1,2,3};
int e[3][3] = { 2,4,3,
                1,5,2,
                6,2,3};
int f[3][3];


void* matricialSingle(void *p)
{
    printf("\nThread Matricial - Processando...\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            c[i][j] = a[i][j] * b[j][i];
        }
    }
}

void* posicionalSingle(void* p)
{
    printf("\nThread Posicional - Processando...\n");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
        f[i][j] += d[i][j] * e[i][j];
        }
    }
}

int main()
{
   printf("Inicio das Threads...\n");

    clock_t t;
    t = clock();

    pthread_create(&thread_1, NULL, matricialSingle, NULL);

    pthread_join(thread_1, NULL);

    t = clock() - t;

    cout << fixed << setprecision(20) << (((float)t) / CLOCKS_PER_SEC) << endl;

    printf("\nResultado da tabela Matricial:\n");


        for(int i = 0;i<3; i++){
                for(int j= 0; j<3;j++){
              printf("%i\t  ",c[i][j]);
                }
                printf("\n");
        }

    pthread_create(&thread_2, NULL, posicionalSingle, NULL);

    pthread_join(thread_2, NULL);


    printf("\nResultado da tabela Posicional:\n");

        for(int i = 0;i<3; i++){
            for(int j= 0; j<3;j++){
                printf("%i\t  ",f[i][j]);
            }
            printf("\n");
        }

    exit(0);
}
