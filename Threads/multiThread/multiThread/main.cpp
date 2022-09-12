#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iomanip>

using namespace std;

int a[3][3] = { 2, 2, 3,
                1, 2, 3,
                1, 2, 3};
int b[3][3] = { 1, 2, 3,
                1, 2, 3,
                1, 2, 3};
int c[3][3];

struct inputs{
 int a;
 int b;
};

void* matricialMulti(void* vargp)
{
    inputs input = *(inputs*)vargp;

    c[input.a][input.b] = a[input.a][input.b] * b[input.b][input.a];
}

void* posicionalMulti(void* vargp)
{
    inputs input = *(inputs*)vargp;

    c[input.a][input.b] = a[input.a][input.b] * b[input.a][input.b];
}

int main()
{
    printf("Inicio das Threads...\n");

    clock_t t;
    t = clock();

     for(int i = 0; i < 3; i++){
            inputs input1;
            inputs input2;
            inputs input3;
            input1.a = input2.a = input3.a = i; // Todos são igual a i;
            input1.b = 0;
            input2.b = 1;
            input3.b = 2;

            pthread_t thread1;
            pthread_t thread2;
            pthread_t thread3;

            pthread_create(&thread1, NULL, matricialMulti, (void *)&input1);

            pthread_create(&thread2, NULL, matricialMulti, (void *)&input2);

            pthread_create(&thread3, NULL, matricialMulti, (void *)&input3);

            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
            pthread_join(thread3, NULL);
    }

    t = clock() - t;

    cout << fixed << setprecision(20) << (((float)t) / CLOCKS_PER_SEC) << endl;

    printf("\nResultado da tabela Matricial\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%i\t  ", c[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    for(int i = 0; i < 3; i++){
            inputs input1;
            inputs input2;
            inputs input3;
            input1.a = input2.a = input3.a = i; // Todos são igual a i;
            input1.b = 0;
            input2.b = 1;
            input3.b = 2;

            pthread_t thread1;
            pthread_t thread2;
            pthread_t thread3;

            pthread_create(&thread1, NULL, posicionalMulti, (void *)&input1);

            pthread_create(&thread2, NULL, posicionalMulti, (void *)&input2);

            pthread_create(&thread3, NULL, posicionalMulti, (void *)&input3);

            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
            pthread_join(thread3, NULL);
    }

    printf("Resultado da tablea Posicional\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%i\t  ", c[i][j]);
        }
        printf("\n");
    }

    exit(0);
}
