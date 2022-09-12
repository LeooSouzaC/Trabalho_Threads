#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>;
#include <time.h>
#include <iomanip>

using namespace std;

int i;
int j;
int valor[100];
int valor2[100];
int resultado[200];
int auxiliar;

struct inputs{
 int a;
 int b;
};

void* ordenador1(void* var) {
    inputs input = *(inputs*)var;

    if(valor[input.a]>valor[input.b]) {
        auxiliar=valor[input.a];
        valor[input.a]=valor[input.b];
        valor[input.b]=auxiliar;
    }
}

void* ordenador2(void*var2) {
  inputs input = *(inputs*)var2;

    if(valor2[input.a]>valor2[input.b]) {
        auxiliar=valor2[input.a];
        valor2[input.a]=valor2[input.b];
        valor2[input.b]=auxiliar;
    }
}

void* ordenadorFinal(void* varFinal) {
    inputs input = *(inputs*)varFinal;

    if(resultado[input.a]>resultado[input.b]) {
        auxiliar=resultado[input.a];
        resultado[input.a]=resultado[input.b];
        resultado[input.b]=auxiliar;
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

    for(i=0; i<100; i++){
        for(j=i+1; j<100; j++){
            inputs input1;
            inputs input2;
            input1.a = input2.a = i;
            input1.b = input2.b = j;

            pthread_t thread_1;
            pthread_t thread_2;

            pthread_create(&thread_1, NULL, ordenador1, (void *)&input1);
            pthread_create(&thread_2, NULL, ordenador2, (void *)&input2);

            pthread_join(thread_1, NULL);
            pthread_join(thread_2, NULL);
        }
    }

    memcpy( resultado, valor, sizeof(valor) );

    memcpy( resultado + 100, valor2, sizeof(valor2) );

    for(i=0; i<200; i++){
        for(j=i+1; j<200; j++){
            inputs inputFinal;
            inputFinal.a = i;
            inputFinal.b = j;

            pthread_t thread_final;

            pthread_create(&thread_final, NULL, ordenadorFinal, (void *)&inputFinal);

            pthread_join(thread_final, NULL);
        }
    }

     t = clock() - t;

    cout << fixed << setprecision(20) << (((float)t) / CLOCKS_PER_SEC) << endl;

    printf("\n");
    for(i=0; i<200; i++){
        printf("%d\n",resultado[i]);
    }
    return 0;
}
