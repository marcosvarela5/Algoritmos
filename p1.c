#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

int sumaSubMax1(int v[], int n){
	int sumaMax = 0;
	int i, j;

	for(i = 0; i < n; i++) {
		int estaSuma = 0;
		for(j = i; j < n; j++) {
			estaSuma = estaSuma + v[j];
			if(estaSuma > sumaMax)
				sumaMax = estaSuma;
		}
	}
	return sumaMax;
}


int sumaSubMax2 (int v[], int n) {
	int j;
	int estaSuma = 0, sumaMax = 0;

	for(j = 0; j < n; j++){
		estaSuma = estaSuma + v[j];
		if(estaSuma > sumaMax)
			sumaMax = estaSuma;
		else if(estaSuma < 0)
			estaSuma = 0;
	}
	return sumaMax;
}


void inicializar_semilla(){
	srand(time(NULL));
	/*nueva semilla de pseudoaleatorios*/
}

void aleatorio(int v[], int n){
	int i, m = 2 * n +  1;
	for(i=0; i < n; i++)
		v[i] = (rand() % m) - n;
	/*generar numeros pseudoaleatorios entre -n y + n*/
}

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t, NULL) <0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void listar_vector(int v[], int n){
	int i;
	printf("[");
	for(i = 0; i<n; i++){
		printf("%2d", v[i]);
	}
	printf("]");
}


void test2() {
	int i, a, b;
	int v[9];
	printf("\ntest2\n");
	printf("%28s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for (i=0; i<10; i++) {
		aleatorio(v, 9);
		listar_vector(v, 9);
		a = sumaSubMax1(v, 9);
		b = sumaSubMax2(v, 9);
		printf("%15d%15d\n", a, b);
	}
}

void test1(){
	int v [6][5] = {{-8, 2, -5, -4, 6}, {4, 0, 9, 2, 5}, {-2, -1, -9, -7, -1}, 
	{9, -2, 1, -7, -8}, {15, -2, -5, -4, 16}, {7, -5, 6, 7, -7}};
	int i;
	printf("test1\n");
	printf("%28s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for(i = 0; i < 6; i++){
		listar_vector(v[i], 5);
		printf("   ");
		printf("%20d", sumaSubMax1(v[i], 5));
		printf("    ");
		printf("%20d\n", sumaSubMax2(v[i], 5));
	}
}

void TiemposAlgoritmoUno(int v[], int n){

	double t, t1, t2, tb, ta, x, y, z;
	int j, cnt=0;
	inicializar_semilla();
	printf("\n    SumaSubMax\n");
    printf("%12s%15s%15s%15s%20s\n", "n", "t(n)", "t(n)/n¹.8", "t(n)/n²", "t(n)/n².2");
	for(n = 500; n <= 32000; n=n*2){
		aleatorio(v,n);
		t1=microsegundos();
		sumaSubMax1(v, n);
		t2=microsegundos();
		t = t2 - t1;

		if(t<500) {
            ta = microsegundos();
            for(j = 0; j<1000; j++) {
                sumaSubMax1(v, n);
            }
            tb = microsegundos();
            t1 = tb - ta;
            t1 = t1/1000;
            t = t1;
            if(t<500)
            cnt++;
        }
        x = t / pow(n, 1.8);
        y = t / pow(n, 2);
        z = t / pow(n, 2.2);
        if(cnt==0)
            printf("%12d%15.4f%15.9f%15.9f%15.9f\n", n, t, x, y, z);
        else{
            printf("(*)%9d%15.4f%15.9f%15.9f%15.9f\n", n, t, x, y, z);
            cnt=0;
		}
	}
}

void TiemposAlgoritmoDos(int v[], int n){

	double t, t1, t2, tb, ta, x, y, z;
	int j, cnt=0;
	inicializar_semilla();
	
	printf("\n    SumaSubMax2\n");
    printf("%12s%15s%15s%15s%20s\n", "n", "t(n)", "t(n)/n⁰.8", "t(n)/n¹", "t(n)/n¹.2");
    //
	for(n = 500; n <= 32000; n=n*2){
		aleatorio(v,n);
		t1=microsegundos();
		sumaSubMax2(v, n);
		t2=microsegundos();
		t = t2 - t1;

		if(t<500) {
            ta = microsegundos();
            for(j = 0; j<1000; j++) {
                sumaSubMax2(v, n);
            }
            tb = microsegundos();
            t1 = tb - ta;
            t1 = t1/1000;
            t = t1;
            cnt++;
        }
        //
        x = t / pow(n, 0.8);
        y = t / pow(n, 1);
        z = t / pow(n, 1.2);

        if(cnt==0)
            printf("%12d%15.4lf%15.9f%15.9f%15.9f\n", n, t, x, y, z);
        else{
            printf("(*)%9d%15.4lf%15.9f%15.9f%15.9f\n", n, t, x, y, z);
            cnt=0;
			}
		}
	}



int main() {
	
	int n=10, v[32000];
	test1();
	test2();
	TiemposAlgoritmoUno(v,n);
	TiemposAlgoritmoDos(v,n);

	}
