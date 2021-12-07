//MARCOS VARELA

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define Swap(x,y) {typeof(x) temp = x; x = y; y = temp;}
#define UMBRAL 1



void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t, NULL) <0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
int i, m=2*n+1;
for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}

void descendente(int v [], int n) {
    int i, j=0;
    for (i=n-1; i >= 0; i--) {
        v[i] = j;
        j++;
    }
}

int ordenado(int v[], int n){
    int i, cnt=0;

    for(i=0; i<n-1; i++){
        if(v[i] > v[i+1])
            cnt++;
    }
    if(cnt == 0)
        return 1;

    return 0;
}

void print_array(int v[], int n){
    int i;
    for(i=0; i<n; i++)
        printf("%d ", v[i]);
}


void ord_ins(int v[], int n){
    int i, x, j;

    for(i = 1; i<n; i++){
        x = v[i];
        j = i-1;

        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}

void mediana3(int v[], int i, int j){
    int k;
    if(i < j){
        k = (i + j) / 2;
        if(v[k] > v[j]) Swap(v[k], v[j]);
        if(v[k] > v[i]) Swap(v[k], v[i]);
        if(v[i] > v[j]) Swap(v[i], v[j]);
    }
}

void ordenarAux(int v[], int izq, int der){
    int pivote;
    int i;
    int j;
    if(izq + UMBRAL <= der){
        mediana3(v, izq, der);
        pivote = v[izq];
        i = izq;
        j = der;
        do{
            do{i += 1;} while(v[i] < pivote);
            do{j -= 1;} while(v[j] > pivote);
            Swap(v[i], v[j])
        }while(j > i);
        Swap(v[i], v[j]);
        Swap(v[izq], v[j]);
        ordenarAux(v, izq, j-1);
        ordenarAux(v, j+1, der);
    }
}

void ord_rapida(int v[], int n){
    ordenarAux(v, 0, n-1);
    if(UMBRAL > 1) ord_ins(v, n);
}

void printAleatorio(int v[], int n){
    printf("\n\nInicialización aleatoria:\n");
    aleatorio(v, n);
    print_array(v, n);
    printf("\nOrdenado? %d", ordenado(v, n));
}

void printAscendente(int v[], int n){
    printf("\n\nInicialización ascendente:\n");
    ascendente(v, n);
    print_array(v, n);
    printf("\nOrdenado? %d", ordenado(v, n));
}

void printDescendente(int v[], int n){
    printf("\n\nInicialización descendente:\n");
    descendente(v, n);
    print_array(v, n);
    printf("\nOrdenado? %d", ordenado(v, n));
}

void printInsercion(int v[], int n){
    printf("\nOrdenacion por Insercion\n");
    ord_ins(v, n);
    print_array(v, n);
    printf("\nOrdenado? %d", ordenado(v, n));
}

void printRapida(int v[], int n){
    printf("\nOrdenacion rápida\n");
    ord_rapida(v, n);
    print_array(v, n);
    printf("\nOrdenado? %d", ordenado(v, n));
}

void copiarArray(int v[], int aux[], int n){
    int i;
    for(i = 0; i < n; i++) {
        aux[i] = v[i];
    }
}

void test(int v[], int n){
    printAscendente(v, n);
    printRapida(v, n);
    printDescendente(v, n);
    printRapida(v, n);
    printAleatorio(v, n);
    printRapida(v, n);

    printf("\n\n\n");
}

void test2(int v[], int n){
    printAscendente(v, n);
    printInsercion(v, n);
    printDescendente(v, n);
    printInsercion(v, n);
    printAleatorio(v, n);
    printInsercion(v, n);

    printf("\n\n\n");
}

void printCabecera(int iter){
    switch (iter) {
        case 0: printf("\n    Ordenacion rápida con inicializacion ascendente y umbral %d\n", UMBRAL);
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/sub", "t(n)/aj", "t(n)/sob");
        
        break;
        case 1: printf("\n    Ordenacion rápida con inicializacion descendente y umbral %d\n", UMBRAL);
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/sub", "t(n)/n^aj", "t(n)/n^sob");
        
        break;
        case 2: printf("\n    Ordenacion rápida con inicializacion aleatoria y umbral %d\n", UMBRAL);
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/sub", "t(n)/aj", "t(n)/n^sob");
        
        break;
    }
}

void printCabecera2(int iter){
    switch(iter){
        case 0: printf("\n    Ordenacion por inserción con inicializacion ascendente \n");
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/n⁰.8", "t(n)/n", "t(n)/(n*(log(n))");
        
        break;
        case 1: printf("\n    Ordenacion por inserción con inicializacion descendente\n");
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/n¹.8", "t(n)/n²", "t(n)/2.2");
        
        break;
        case 2: printf("\n    Ordenacion por inserción con inicializacion aleatoria \n");
        printf("%12s%15s%13s%17s%15s\n", "Tam.", "Tiempo", "C. sub.", "C. aj.", "C. sob.");
        printf("%12s%15s%13s%17s%15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
        
        break;
    }
}

double tiemposQuicksort(int n, int j){
    int v[32000];
    double t1, t2;

    switch (j) {
        case 0: ascendente(v, n);
        t1 = microsegundos();
        ord_rapida(v, n);
        t2 = microsegundos();
        break;
        case 1: descendente(v, n);
        t1 = microsegundos();
        ord_rapida(v, n);
        t2 = microsegundos();
        break;
        case 2: aleatorio(v, n);
        t1 = microsegundos();
        ord_rapida(v, n);
        t2 = microsegundos();
        break;
    }
    return (t2 - t1);
}

double tiemposInsercion(int n, int j){
    int v[32000];
    double t1, t2;

    switch (j) {
        case 0: ascendente(v, n);
        t1 = microsegundos();
        ord_ins(v, n);
        t2 = microsegundos();
        break;
        case 1: descendente(v, n);
        t1 = microsegundos();
        ord_ins(v, n);
        t2 = microsegundos();
        break;
        case 2: aleatorio(v, n);
        t1 = microsegundos();
        ord_ins(v, n);
        t2 = microsegundos();
        break;
    }
    return (t2 - t1);
}

double tiempos500Quicksort(int n, int j){
    int v[32000];
    double t1, t2, ta, tb;

    switch (j) {
        case 0:
        ascendente(v, n);
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            ord_rapida(v, n);
        }
        t2 = microsegundos();
        return (t2 - t1)/1000;
        case 1:
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            descendente(v, n);
            ord_rapida(v, n);
        }
        t2 = microsegundos();
        ta = microsegundos();
        for (j = 0; j < 1000; j++) {
            descendente(v, n);
        }
        tb = microsegundos();
        return ((t2 - t1) - (tb - ta))/1000;
        case 2:
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            aleatorio(v, n);
            ord_rapida(v, n);
        }
        t2 = microsegundos();
        ta = microsegundos();
        for (j = 0; j < 1000; j++) {
            aleatorio(v, n);
        }
        tb = microsegundos();
    }
    return ((t2 - t1) - (tb - ta))/1000;
}

double tiempos500Insercion(int n, int j){
    int v[32000];
    double t1, t2, ta, tb;

    switch (j) {
        case 0:
        ascendente(v, n);
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            ord_ins(v, n);
        }
        t2 = microsegundos();
        return (t2 - t1)/1000;
        case 1:
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            descendente(v, n);
            ord_ins(v, n);
        }
        t2 = microsegundos();
        ta = microsegundos();
        for (j = 0; j < 1000; j++) {
            descendente(v, n);
        }
        tb = microsegundos();
        return ((t2 - t1) - (tb - ta))/1000;
        case 2:
        t1 = microsegundos();
        for (j = 0; j < 1000; j++) {
            aleatorio(v, n);
            ord_ins(v, n);
        }
        t2 = microsegundos();
        ta = microsegundos();
        for (j = 0; j < 1000; j++) {
            aleatorio(v, n);
        }
        tb = microsegundos();
    }

    return ((t2 - t1) - (tb - ta))/1000;
}


int main(){
    int n=10, v[32000], i, cnt=0, j;
    double t, x, y, z;

    inicializar_semilla();

    test(v, n);
    test2(v, n);

    for(i=0; i<3; i++) {
        printCabecera(i);
        for (n = 500; n <= 32000; n = n * 2) {
            t = tiemposQuicksort(n, i);
            if (t < 500) {
                t = tiempos500Quicksort(n, i);
                cnt++;
            }

        switch(i){
            case 0:
            x = t / n;
            y = t / pow(n, 1.07);
            z = t / pow(n, 1.25);
            break;

            case 1:
            x = t / n;
            y = t / pow(n, 1.07);
            z = t / pow(n, 1.16);
            break;

            case 2:
            x = t / n;
            y = t / pow(n ,1.08);
            z = t / (n*log(n));
            break;
            }
            if (cnt == 0){
                printf("%12d%15.4f%15.5f%15.5f%15.5f\n", n, t, x, y, z);
            }
            else {
                printf("(*)%9d%15.5f%15.5f%15.5f%15.5f\n", n, t, x, y, z);
                cnt = 0;
            }
        }
    }

    for(j=0; j<3; j++) {
        printCabecera2(j);
        for (n = 500; n <= 32000; n = n * 2) {
            t = tiemposInsercion(n, j);
            if (t < 500) {
                t = tiempos500Insercion(n, j);
                cnt++;
            }

            switch(j){
            case 0:
            x = t / pow(n, 0.8);
            y = t / n;
            z = t / (n * log(n));
            break;

            case 1:
            x = t / pow(n, 1.8);
            y = t / pow(n, 2);
            z = t / pow(n, 2.2);
            break;

            case 2:
            x = t / pow(n, 1.8);
            y = t / pow(n, 2);
            z = t / pow(n, 2.2);
            break;
            }
            
            if (cnt == 0){
                printf("%12d%15.5f%15.5f%15.5f%15.5f\n", n, t, x, y, z);
            }
            else {
                printf("(*)%9d%15.5f%15.5f%15.5f%15.5f\n", n, t, x, y, z);
                cnt = 0;
            }
        }
    }
}

