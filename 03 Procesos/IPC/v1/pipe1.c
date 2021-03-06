#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_PROC 4

void proceso_padre(int pipefd[]);
void proceso_hijo(int np, int pipefd[]);

int main()
{	
	pid_t pid;
	register int np;
	int pipefd[2];  // File descriptor
	int edo_pipe;

	printf("Probando procesos\n");

	edo_pipe = pipe(pipefd);

	if (edo_pipe == -1)
	{
		perror("Error al crear la tuberia (pipe)...\n");
		exit(EXIT_FAILURE);
	}


	for (np = 0; np < NUM_PROC; np++)
	{
		pid = fork();

		// Verificamos si hay un error
		if (pid == -1)
		{
			perror("Error al crear el proceso\n");
			exit(EXIT_FAILURE);
		}

		// Si pid es 0 : es el hijo
		if (!pid)
		{
			// le pasamos el numero de proceso (np)
			proceso_hijo(np, pipefd);
		}
	}
	proceso_padre(pipefd);

	return 0;
}

void proceso_padre(int pipefd[])
{
	register int np;
	pid_t pid;
	int estado, numproc, resultado;

	close(pipefd[1]);

	for (np = 0; np < NUM_PROC; np++)
	{
		
		pid = wait(&estado);  	// Aqui nos dice que ya acabo el proceso hijo
		read(pipefd[0], &resultado, sizeof(int)); // Usamos el descriptor de lectura
		numproc = estado >> 8;	// El estado regresara el número del proceso

		if (numproc == 0)
		{
			printf("Termina el proceso %d con PID %d\t", numproc, pid);
			printf("La suma es: %d\n", resultado);
		}
		else if (numproc == 1)
		{
			printf("Termina el proceso %d con PID %d\t", numproc, pid);
			printf("La resta es: %d\n", resultado);
		}
		else if (numproc == 2)
		{
			printf("Termina el proceso %d con PID %d\t", numproc, pid);
			printf("La multiplicacion es: %d\n", resultado);
		}
		else if (numproc == 3)
		{
			printf("Termina el proceso %d con PID %d\t", numproc, pid);
			printf("La division es: %d\n", resultado);
		}
	}
	close(pipefd[0]);
}

void proceso_hijo(int np, int pipefd[])
{
	int num1 = 20, num2 = 4;
	int suma, resta, multi, divi;

	close(pipefd[0]);

	if (np == 0)
	{
		suma = num1 + num2;
		write(pipefd[1], &suma, sizeof(int));	// descriptor de escritura de la tuberia
	}
	else if (np == 1)
	{
		resta = num1 - num2;
		write(pipefd[1], &resta, sizeof(int));	// descriptor de escritura de la tuberia
	}
	else if (np == 2)
	{
		multi = num1 * num2;
		write(pipefd[1], &multi, sizeof(int));	// descriptor de escritura de la tuberia
	}
	else if (np == 3)
	{
		divi = num1 / num2;
		write(pipefd[1], &divi, sizeof(int));	// descriptor de escritura de la tuberia
	}

	// Y en la tubería vamos a mandar el resultado
	// Dependiendo de la operacion
	//pip[1] - Tiene el descriptor de escritura
	//descriptor, bola de datos, cantidad de la bola de datos
	close(pipefd[1]); // Cerramos el descriptor de escritura para el proceso hijo

	// Regresamos el número de proceso para saber quien termina
	exit(np);
}
