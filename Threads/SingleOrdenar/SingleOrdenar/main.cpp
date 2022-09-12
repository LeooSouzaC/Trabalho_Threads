#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>;
#include <time.h>
#include <iomanip>

using namespace std;

pthread_t thread_1;
pthread_t thread_2;
pthread_t thread_3;

int i;
int j;
int valor[100];
int valor2[100];
int resultado[200];
int auxiliar;

void* ordenador1(void* p) {
    for(i=0; i<100; i++){
        for(j=i+1; j<100; j++){
            if(valor[i]>valor[j]) {
                auxiliar=valor[i];
                valor[i]=valor[j];
                valor[j]=auxiliar;
            }
        }
    }
}

void* ordenador2(void* p) {
    for(i=0; i<100; i++){
        for(j=i+1; j<100; j++){
            if(valor2[i]>valor2[j]) {
                auxiliar=valor2[i];
                valor2[i]=valor2[j];
                valor2[j]=auxiliar;
            }
        }
    }
}

void* ordenadorFinal(void* p) {
    for(i=0; i<200; i++){
        for(j=i+1; j<200; j++){
            if(resultado[i]>resultado[j]) {
                auxiliar=resultado[i];
                resultado[i]=resultado[j];
                resultado[j]=auxiliar;
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    for(i=0; i<100; i++) {
      valor[i] = rand() % 200;
    }

    for(i=0; i<100; i++) {
      valor2[i] = rand() % 200;
    }

    clock_t t;
    t = clock();

    pthread_create(&thread_1, NULL, ordenador1, NULL);

    pthread_join(thread_1, NULL);

    pthread_create(&thread_2, NULL, ordenador2, NULL);

    pthread_join(thread_2, NULL);

    memcpy( resultado, valor, sizeof(valor) );

    memcpy( resultado + 100, valor2, sizeof(valor2) );

    pthread_create(&thread_3, NULL, ordenadorFinal, NULL);

    pthread_join(thread_3, NULL);

    t = clock() - t;

    cout << fixed << setprecision(20) << (((float)t) / CLOCKS_PER_SEC) << endl;

    printf("\n");
    for(i=0; i<200; i++){
        printf("%d\n",resultado[i]);
    }
    return 0;
}
