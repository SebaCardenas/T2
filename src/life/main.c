#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "stack.h"
#include <sys/mman.h>


int main(int argc, char *argv[])
{
	if (argc != 2 && argc != 3)
	{
		printf("Modo de uso: ./life test.txt [tiempo]\n");
		return 0;
	}

	/* Abrimos el archivo input en modo de lectura */
	FILE *input_file = fopen(argv[1], "r");

	/* Abrimos el archivo output en modo de escritura */
	FILE *output_file = fopen("output.csv", "w");

	/* Revisa que el archivo fue abierto correctamente */
	if (!input_file)
	{
		printf("¡El archivo %s no existe!\n", argv[1]);
		return 2;
	}




	/* Definimos y asignamos las constantes del problema */
	int n; int A; int B; int C; int D;
	fscanf(input_file, "%d %d %d %d %d", &n, &A, &B, &C, &D);


	int tiempo_max = atoi(argv[2]);

	char line[256];
	char palabra[256];
	int contador2 = 0;
	int contador = 0;
	char name[256];
	int ids = 1;

	Stack *tablas;
	Stack_Dato *posiciones;
	tablas = stack_init();

	while(fgets(line, sizeof(line), input_file)!=NULL){
		char *puntero_palabra;
		puntero_palabra = (char *) malloc(sizeof(char));
		posiciones = stack_dato_init();
		memset(palabra, 0, sizeof palabra);
		for (size_t i = 0; i < strlen(line); i++) {

			if (line[i] == ' ' || line[i] == '\n' ) {
				if (contador == 0){
					strcpy(puntero_palabra,palabra);
					contador++;
				}
				else{
					push_dato(posiciones, atoi(palabra));
					if (posiciones->tail==NULL) {
						posiciones->tail=posiciones->head;
					}
				}
				contador2=0;
				memset(palabra, 0, sizeof palabra);
			}
			else{
				palabra[contador2] = line[i];
				contador2++;
			}
		}

		push(tablas, posiciones, puntero_palabra, ids);
		ids ++;
		contador = 0;

	}
	Node*actual;
	Node*Next;
	actual = tablas->head;
	Next = actual->next;

struct vivas * estado;
estado = (struct vivas *) malloc(sizeof(struct vivas));
estado->live=0;
glob_var = 1;
glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE,
								MAP_SHARED | MAP_ANONYMOUS, -1, 0);

for(int i=0;i<tablas->len-1;i++)
    {
        if(vfork() == 0)
        {
					GameOfLife(actual,A,B,C,D,tiempo_max,output_file, estado);
						_exit(0);
        }


				actual = Next;
				Next=actual->next;
    }
//
for (size_t l = 0; l < tablas->len-1; l++) {
	wait(NULL);
}
//printf("jejejeje\n" );
//printf("------------%d---------------%d\n",estado,estado->live);





/*
	Node *actual_tabla;
	Node *siguiente_tabla;

	actual_tabla = tablas->head;
	siguiente_tabla = actual_tabla->next;
	for (size_t i = 0; i < tablas->len; i++) {
		Dato *actual_dato;
		Dato *siguiente_dato;
		actual_dato = actual_tabla->dato->head;
		siguiente_dato = actual_dato->next;
		printf("%s\n",actual_tabla->name);

		for (size_t j = 0; j < actual_tabla->dato->len; j++) {
			printf("%d",actual_dato->posicion);
			if (siguiente_dato == NULL) {
				break;
			}
			actual_dato = siguiente_dato;
			siguiente_dato = actual_dato->next;
		}
		printf("\n" );

		printf("2------------%s\n",actual_tabla->name);
		actual_tabla = siguiente_tabla;
		siguiente_tabla = actual_tabla->next;
		printf("1------------\n");
		if (siguiente_tabla == NULL) {
			printf("hice break\n" );
			break;
		}
	}
	*/
	/* Cerramos los archivos correctamente */


	fclose(input_file);
	fclose(output_file);

	return 0;
}
