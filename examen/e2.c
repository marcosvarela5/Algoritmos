#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos() {
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0) return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[], int n) {
    /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n) {
    int i, k = n;
    for (i = 0; i < n; i++) {
        v[i] = k;
        k--;
    }
}

bool estaOrdenado(int v[], int length) {
    int i;

    for (i = 0; i < length - 1; i++) {
        if (v[i] > v[i + 1])
            return false;
    }

    return true;
}

void listar_vector(int v[], int length) {
    int i;

    printf("[");
    for (i = 0; i < length; i++) {
        if (i == length - 1) printf("%d", v[i]);
        else printf("%d, ", v[i]);
    }
    printf("]\t");
}

void ord_sel(int v[], int n){

    int i, minj, minx, j;

    for (i = 0; i < n - 1; i++) {
        minj = i;
        minx = v[i];

        for (j = i + 1; j < n; ++j) {

            if(v[j] < minx){
                minj = j;
                minx = v[j];
            }
        }
        v[minj] = v[i];
        v[i] = minx;
    }
}

void auxord(int v[], int iz, int dr){

    int j, i, aux1, aux2;

    if(iz < dr){
        j = dr;
        for(i = dr - 1; i >= iz; i--){
            if(v[i] > v[dr]){
                j = j - 1;
                aux1 = v[i];
                v[i] = v[j];
                v[j] = aux1;
            }
        }
        aux2 = v[j];
        v[j] = v[dr];
        v[dr] = aux2;
        auxord(v, iz, j - 1);
        auxord(v, j + 1, dr);
    }

}

void ordenar(int v[], int n){
auxord(v, 0, n);
}

void imp_gen(int v[], int p, void (*func) (int v[], int n),
             void (*v_init) (int v[], int n)) {
    int k;
    double ta, tb, t, t2, t3, x, y, z;

    ta = microsegundos();
    func(v, p);
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        for (k = 0; k < 1000; k++) {
            v_init(v, p);
            func(v, p);
        }
        tb = microsegundos();
        t2 = tb - ta;

        ta = microsegundos();
        for (k = 0; k < 1000; k++)
            v_init(v, p);
        tb = microsegundos();
        t3 = tb - ta;

        t = (t2 - t3) / k;
    }

    if (func == ordenar) {
        x = t / p;
        if(v_init == descendente){
            y = t / (pow(p,1.155));
        }else{
            y = t / (pow(p,1.2));
        }
        z = t / pow(p, 1.5);
        printf("%12d%15.3f%15.6f%15.6f%15.6f\n", p, t, x, y, z);
    }
    else {
        x = t / (pow(p,1.8));
        y = t / (pow(p,2));
        z = t / (pow(p, 2.2));
        printf("%12d%15.3f%15.6f%15.6f%15.6f\n", p, t, x, y, z);
    }
}

void imp_asc(int v[], int p, void (*func) (int v[], int n)) {
    int k;
    double ta, tb, t, x, y, z;

    ta = microsegundos();
    func(v, p);
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        ta = microsegundos();
        for (k = 0; k < 1000; k++) {
            func(v, p);
        }
        tb = microsegundos();
        t = tb - ta;

        t /= k;
    }

    if (func == ordenar) {
        x = t / p;
        y = t / pow(p,1.165);
        z = t / pow(p, 1.5);
        printf("%12d%15.3f%15.6f%15.6f%15.6f\n", p, t, x, y, z);
    }
    else {
        x = t / (pow(p,1.8));
        y = t / (pow(p,2));
        z = t / (pow(p,2.2));
        printf("%12d%15.3f%15.6f%15.6f%15.6f\n", p, t, x, y, z);
    }
}

void test(int v[], int length, void (*func) (int v[], int n)) {
    printf("\nInicialización aleatoria\n");
    aleatorio(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI");
    else printf("NO");
    if (func == ord_sel) printf("\nOrdenación por selección:\n");
    else printf("\nOrdenación por shell:\n");
    func(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI");
    else printf("NO");
    printf("\n\nInicialización descendente\n");
    descendente(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI");
    else printf("NO");
    if (func == ord_sel) printf("\nOrdenación por selección:\n");
    else printf("\nOrdenación por shell:\n");
    func(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI");
    else printf("NO");
    printf("\n\nInicialización ascendente\n");
    ascendente(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI");
    else printf("NO");
    if (func == ord_sel) printf("\nOrdenación por selección:\n");
    else printf("\nOrdenación por shell:\n");
    func(v, length);
    listar_vector(v, length);
    printf("\nOrdenado? -> ");
    if (estaOrdenado(v, length)) printf("SI\n\n");
    else printf("NO\n\n");
}

void complejidad(){
    int v[32000], p;
    //descendente
    printf("\n\n---------------DESCENDENTE----------------\n");
    printf("Ordenacion por shell de vector DESCENDENTE:\n");
    for (p = 500; p <= 32000; p *= 2){
        descendente(v, p);
        imp_gen(v, p, ordenar, descendente);
    }
    //aleatorio
    printf("\n\n---------------ALEATORIO----------------\n");
    printf("Ordenacion por shell de vector ALEATORIO:\n");
    for (p = 500; p <= 32000; p *= 2){
        aleatorio(v, p);
        imp_gen(v, p, ordenar, aleatorio);
    }
    //ascendente
    printf("\n\n---------------ASCENDENTE----------------\n");
    printf("Ordenacion por shell de vector ASCENDENTE:\n");
    for (p = 500; p <= 32000; p *= 2){
        ascendente(v, p);
        imp_asc(v, p, ordenar);
    }
}

int main() {
    int i;
    int v_par[10] = {1, 5, 3, 6, 8, 2, 4, 6, 8, 3},
            length_par = (sizeof(v_par) / sizeof(v_par[0]));
    int v_impar[9] = {1, 5, 3, 6, 8, 2, 4, 6, 8},
            length_impar = (sizeof(v_impar) / sizeof(v_impar[0]));

    inicializar_semilla();

    printf("\n--------------------------------------\n");
    printf("TEST CON VECTOR PAR:\n");
    test(v_par, length_par, ordenar);
    printf("\n\n--------------------------------------\n");
    printf("TEST CON VECTOR IMPAR:\n");
    test(v_impar, length_impar, ordenar);

    for (i = 1; i <= 3; ++i) {
        printf("\n\nTablas de complejidad intento %d de 3:\n", i);
        complejidad();
        printf("-------------------------------\n");
    }

    return 0;
}

