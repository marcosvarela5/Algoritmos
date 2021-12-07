//MARCOS VARELA
//HUGO CASTRO
//NAIM RIVERA

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define TAM_MAX 1600
#define true 1
#define false 0
#define MI __INT_MAX__
typedef char byte;

typedef int ** matriz;
typedef struct {
	int x, y, peso;
} arista;

typedef arista tipo_elemento;
typedef struct {
	int cabeza, final, tamano;
	tipo_elemento vector[TAM_MAX];
} cola;


void inicializar_semilla() {
    srand(time(NULL));
    /* se establece la semilla de una nueva serie de enteros
       pseudo-aleatorios */
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void crear_cola(cola *c){
    c->tamano = 0;
    c->cabeza = 0;
    c->final = -1;
}
int cola_vacia(cola c) {
    return (c.tamano == 0);
}
void incrementar(int *x) {
    if (++(*x) == TAM_MAX)
        *x = 0;
}

void insertar(tipo_elemento x, cola *c){
    if (c->tamano == TAM_MAX) {
        printf("error: cola llena: %d\n", c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = x;
}

tipo_elemento primero(cola c){
    if (cola_vacia(c)) {
    printf("error: cola vacia\n"); exit(EXIT_FAILURE);
    }
    return(c.vector[c.cabeza]);
    }

tipo_elemento quitar_primero(cola *c){
    tipo_elemento x;
    if (cola_vacia(*c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}

void mostrar_cola(cola c){
    int i;
    printf("\nAristas:");
    for (i = 0; i < c.tamano; i++) {
        printf("(%d, %d)", c.vector[i].x, c.vector[i].y);
    }
  
}


matriz crear_matriz(int n) {
	int i;
	matriz aux;
	if ((aux = malloc(n*sizeof(int *))) == NULL)
	return NULL;
	for (i=0; i<n; i++)
	if ((aux[i] = malloc(n*sizeof(int))) == NULL)
		return NULL;
	return aux;
}

void inicializar_matriz(matriz m, int n) {

	int i, j;
	for (i=0; i<n; i++){
		for (j=i+1; j<n; j++){
		m[i][j] = rand() % n + 1;
		}
	}

	for (i=0; i<n; i++){
		for (j=0; j<=i; j++){
		if (i==j){
			m[i][j] = 0;
		}
		else{
			m[i][j] = m[j][i];
			}
		}
	}
}

void liberar_matriz(matriz m, int n) {
	int i;
	for (i=0; i<n; i++){
		free(m[i]);
	}
	free(m);
}

void printMatriz(matriz m, int n) {
    int i,j;
    for (i = 0; i < n; i++) {
        printf("[");
        for (j = 0; j < n; j++) {
            printf(" %2i ",m[i][j]);
        }
        printf("]\n");
    }
}

void prim(matriz m, int nodos, cola *aristas) {

	int min, i, j, cont = 0, k=0;
	arista a;
	int *masProximo = (int *) malloc(nodos*sizeof(int));
	int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
	crear_cola(aristas);
	distanciaMinima[0] = -1;
	for(i = 1; i < nodos; i++) {
		masProximo[i] = 0;
		distanciaMinima[i] = m[i][0];
	}

	do{
			min = __INT_MAX__;
			for(j = 1; j < nodos; j++){
				if(0 <= distanciaMinima[j] && distanciaMinima[j] < min){
					min = distanciaMinima[j];
					k = j;
				}
			}
		
		a.x = masProximo[k];
		a.y = k;
		a.peso = distanciaMinima[k];
		insertar(a, aristas);
		distanciaMinima[k] = -1;
		for(j = 1; j < nodos; j++){
			if(m[j][k] < distanciaMinima[j]){
				distanciaMinima[j] = m[j][k];
				masProximo[j] = k;
			}
		} cont++;
	} while(cont < nodos - 1);

	free(masProximo);
	free(distanciaMinima);
}

double medir_tiempo(int tam, int k){
//K es el número de repeticiones en caso de tener que medir tiempos pequeños
    double t_inicio = 0.0; //tiempo de inicio
    double t_fin = 0.0; //tiempo de fin
    double t_test = 0.0; //tiempo del test
    int i; //Iterador

	cola cola;
    matriz mat;
    mat = crear_matriz(tam);
    inicializar_matriz(mat, tam);
    t_inicio = microsegundos();
    prim(mat, tam, &cola); 
    t_fin = microsegundos();
    t_test = t_fin - t_inicio;
    if (t_test < 500){
        printf("(*)");
        t_inicio = microsegundos();
        for (i = 0; i < k; i++){
            prim(mat, tam, &cola);
        }
        t_fin = microsegundos();
        t_test = (t_fin - t_inicio) / k;
    }
    liberar_matriz(mat, tam);

    return t_test;
}

void print_matriz(matriz m, int tamano){
    int i, j;
    for(i = 0; i< tamano; i++){
        for(j = 0; j < tamano; j++){
            printf("%d", m[i][j]);
        }
    }
}

void print_algoritmo(){
    int k = 1000;
    double tiempo = 0.0;
    int n; //Iterador
    printf("\n\tAlgoritmo de Prim:\n");
    printf("\t       n\t\t   t(n)\t\t   t(n)/(n^1.85)"
            "\t\t  t(n)/(n^2.1)\t\t   t(n)/(n^2.25)\n");
    for (n=15; n<=1000; n*=2){
        tiempo = medir_tiempo(n, k);
        printf("\t% 6d\t\t% 15.4f\t\t% 14.8f\t\t% 14.8f\t\t% 14.8f\n",
               n, tiempo, tiempo/(pow(n,1.85)),
               tiempo/(pow(n,2.1)),
               tiempo/(pow(n,2.25)));
    }

    printf("\n");
    printf("\n\n (*) Tiempo promedio en %d ejecuciones del algoritmo\n\n",k);
}


 void test1(){
    int tam = 5;
    int peso = 0;
    int i;
    cola cola;
    matriz m = crear_matriz(tam);
    m[0][0] = 0; m[0][1] = 1; m[0][2] = 8; m[0][3] = 4; m[0][4] = 7;
    m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 6; m[1][4] = 5;
    m[2][0] = 8; m[2][1] = 2; m[2][2] = 0; m[2][3] = 9; m[2][4] = 5;
    m[3][0] = 4; m[3][1] = 6; m[3][2] = 9; m[3][3] = 0; m[3][4] = 3;
    m[4][0] = 7; m[4][1] = 5; m[4][2] = 5; m[4][3] = 3; m[4][4] = 0;

    prim(m, tam, &cola);
    mostrar_cola(cola);
    for (i = 0; i < cola.tamano; i++) {
        peso += cola.vector[i].peso;
    }
    printf("\nPeso: %d", peso);
}

void test2(){
    int tam = 4;
    int i, peso = 0;
    cola cola;
    matriz m = crear_matriz(tam);
    m[0][0] = 0; m[0][1] = 1; m[0][2] = 4; m[0][3] = 7;
    m[1][0] = 1; m[1][1] = 0; m[1][2] = 2; m[1][3] = 8;
    m[2][0] = 4; m[2][1] = 2; m[2][2] = 0; m[2][3] = 3;
    m[3][0] = 7; m[3][1] = 8; m[3][2] = 3; m[3][3] = 0;


    prim(m, tam, &cola);
    mostrar_cola(cola);
    for (i = 0; i < cola.tamano; i++) {
        peso += cola.vector[i].peso;
    }
    printf("\nPeso: %d", peso);
}

void test3(){ // MI es MAXINT, lo defino por motivos visuales
    int tam = 7;
    int peso = 0;
    int i;
    cola cola;
    matriz m = crear_matriz(tam);
    m[0][0] = 0; m[0][1] = 7; m[0][2] = MI; m[0][3] = 5; m[0][4] = MI; m[0][5] = MI; m[0][6] = MI;
    m[1][0] = 7; m[1][1] = 0; m[1][2] = 8; m[1][3] = 9; m[1][4] = 7; m[1][5] = MI; m[1][6] = MI;
    m[2][0] = MI; m[2][1] = 8; m[2][2] = 0; m[2][3] = MI; m[2][4] = 5; m[2][5] = MI; m[2][6] = MI;
    m[3][0] = 5; m[3][1] = 9; m[3][2] = MI; m[3][3] = 0; m[3][4] = 15; m[3][5] = 6; m[3][6] = MI;
    m[4][0] = MI; m[4][1] = 7; m[4][2] = 5; m[4][3] = 15; m[4][4] = 0; m[4][5] = 8; m[4][6] = 9;
    m[5][0] = MI; m[5][1] = MI; m[5][2] = MI; m[5][3] = 6; m[5][4] = 8; m[5][5] = 0; m[5][6] = 11;
    m[6][0] = MI; m[6][1] = MI; m[6][2] = MI; m[6][3] = MI; m[6][4] = 9; m[6][5] = 11; m[6][6] = 0;

    prim(m, tam, &cola);
    mostrar_cola(cola);
    for (i = 0; i < cola.tamano; i++) {
        peso += cola.vector[i].peso;
    }
    printf("\nPeso: %d", peso);
}


int main(){
	inicializar_semilla();
    test1();
    test2();
    test3();
	print_algoritmo();
}