#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funcHilo(void * arg);

int main()
{	
	register int nh;
	pthread_t tids[NUM_HILOS];  // Arreglo de identificadores
	int *resultado, nhs[NUM_HILOS];
	
	printf("Ejemplo de hilos\n");

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		// Le mandamos cada variable para cada numero de hilo
		nhs[nh] = nh;
		// tid, atributos, la funcion a ejecutar, parametros
		// Le mandamos el número del hilo
		pthread_create(&tids[nh], NULL, funcHilo, (void *)&nhs[nh]);

		// Cada llamada a funcion va a tener un indice diferente 
		// &nhs[nh]) a cada indice se le manda el indice de una varibale propia
		// 2a variable al 2o hilo

		// Si le mando solo una direccion
		//se queda con la ultima direccio o valor del ciclo


		// En hilos es paso por referencia y en tuberias es paso por direcciones

	}

	// , lo que retorna el valor del hilo

	for (nh = 0; nh < NUM_HILOS; nh++)
	{
		pthread_join(tids[nh], (void **)&resultado);
		printf("El resultado es: %d\n", *resultado);
	}

	return 0;
}

void * funcHilo(void * arg)
{
	// Primero casteo y luego obtengo su contenido
	int nh = *(int *)arg; 
	int num1 = 20, num2 = 4;
	int *res = malloc(sizeof(int));   // el resultado de cada operacion tiene de estar en vv.aa diferentes
									  // también podria usarse un arreglo

	printf("Hilo %d en ejecución.\n", nh);
	
	// Aqui hago la paralelización
	if (nh == 0)
	{
		*res = num1 + num2;
	}
	else if (nh == 1)
	{
		*res = num1 - num2;
	}
	else if (nh == 2)
	{
		*res = num1 * num2;
	}
	else if (nh == 3)
	{
		*res = num1 / num2;
	}

	pthread_exit((void *)res);
}