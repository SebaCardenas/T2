#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>

Stack *stack_init()
{
  /* Aqui agrega tu código */
  struct stack *primero;
  primero = (struct stack *) malloc(sizeof(struct stack));
  primero-> head = NULL;
  primero-> len = 0;
  return primero;
}

Stack_Matrix *matrix_init()
{
  /* Aqui agrega tu código */
  struct stack_matrix *primero;
  primero = (struct stack_matrix *) malloc(sizeof(struct stack));
  primero-> head = NULL;
  primero-> len = 0;
  return primero;
}

Stack_Dato *stack_dato_init()
{
  /* Aqui agrega tu código */
  struct stack_dato *primero;
  primero = (struct stack_dato *) malloc(sizeof(struct stack_dato));
  primero-> head = NULL;
  primero-> tail = NULL;
  primero-> len = 0;
  return primero;
}

Cell *cell_init()
{
  /* Aqui agrega tu código */
  struct cell *primero;
  primero = (struct cell *) malloc(sizeof(struct cell));
  primero-> live = 0;
  return primero;
}
/* Recordatorio, struct node == Node, cuando definimos struct node Node*/
void push(Stack* stack,Stack_Dato* stack_dato, char *name, int id)
{
  Node *ball;
  ball = (Node *)malloc(sizeof(Node));
  ball -> name = name;
  ball -> dato = stack_dato;
  ball -> next = stack -> head;
  ball -> ID = id;
  stack -> head = ball;
  stack -> len += 1;
}

void push_mtx(Stack_Matrix* stack_matrix, Cell **matrix) {
  struct mi_mtx *mat;
  mat = (struct mi_mtx *)malloc(sizeof(struct mi_mtx));
  mat->next=stack_matrix->head;
  mat->matrix = matrix;
  stack_matrix->head = mat;
  stack_matrix->len+=1;
}

void push_dato(Stack_Dato* stack_dato, int posicion)
{
  Dato *ball;
  ball = (Dato *)malloc(sizeof(Dato));
  ball -> posicion = posicion;
  ball -> next = stack_dato -> head;
  stack_dato -> head = ball;
  stack_dato -> len += 1;
}

int pop(Stack_Dato* stack)
{
  int pos;
  Dato *POPpos;
  POPpos = stack->head;
  stack -> head = POPpos-> next;
  stack->len -=1;
  pos=POPpos->posicion;
  free(POPpos);
  return pos;
}

Node* pop_node(Stack* stack){
  Node *POPpos;
  POPpos = stack->head;
  stack -> head = POPpos-> next;
  stack->len--;
  return POPpos;
}

void crear_tablero(Node *tablero, Cell **matrix,int D) {


    int contador;
    int contador2;
    int x;
    int y;

    contador = 0;
    contador2 = 0;
    Cell *celula;
    while (tablero->dato->len != 0) {
      if (tablero->dato->head==tablero->dato->tail && tablero->dato->len ==1) {
        break;
      }
      if (contador%2==0) {
        y = pop(tablero->dato);
        contador2++;
      }
      else{
        x = pop(tablero->dato);
        contador2++;
      }
      if (contador2==2){
        celula = &matrix[D-y-1][x];
        celula->live = 1;
        contador2=0;
      //  printf("%d %d\n",x, y);
      }

      contador++;
    }

}

void mostrar_tablero(Cell ** matrix, int D, Node *tabla) {
    int contador = D-1;
    printf("%s\n",tabla->name);
    for(int i=0;i<D;i++){
      printf(" |");
  		for(int j=0;j<D;j++){
  			struct cell *mi_cell;
  			mi_cell =  &matrix[i][j];
        if (mi_cell->live==1) {
          printf("\u25A0 ");
        }
        else if(mi_cell->live==0){
          printf("\u25A1 ");

        }
  		}
      printf("| %d\n", contador);
      contador--;
  	}
    printf("\n" );
}

void guardar_estado(Stack_Matrix* stack_matrix, Cell **matrix,int A,int B,int C,int D, int tiempo_simulacion){
  int estado = tiempo_simulacion%4;
  struct mi_mtx *actual_mtx;
  struct mi_mtx *actual_mtx_next;
  actual_mtx = stack_matrix->head;
  actual_mtx_next = actual_mtx->next;
  for (int i = 0; i < estado; i++) {
    actual_mtx = actual_mtx_next;
    if (i==3) {
      actual_mtx = actual_mtx_next;
      break;
    }
    actual_mtx_next = actual_mtx->next;
  }
  for(int i=0;i<D;i++){
    for(int j=0;j<D;j++){
      actual_mtx->matrix[i][j] =  matrix[i][j];

    }


  }
}

void resetear_tablero(Cell ** matrix, int D){
  for(int i=0;i<D;i++){
    for(int j=0;j<D;j++){
      struct cell *mi_cell;
      mi_cell =  &matrix[i][j];
      mi_cell->live = 0;
    }
  }
}

void checkear_condiciones(Cell ** matrix,int A, int B,int C, int D){
  int cercanos = 0;

  for(int i=0;i<D;i++){

    for(int j=0;j<D;j++){
      struct cell *mi_cell;
      struct cell *mi_cell_arriba;
      struct cell *mi_cell_abajo;
      struct cell *mi_cell_derecha;
      struct cell *mi_cell_izquierda;

      struct cell *mi_cell_arribaD;
      struct cell *mi_cell_abajoD;
      struct cell *mi_cell_arribaI;
      struct cell *mi_cell_abajoI;

      mi_cell =  &matrix[i][j];
      if (i+1 < D) {
        mi_cell_arriba=&matrix[i+1][j];
        if (mi_cell_arriba->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_arriba=NULL;
      }
      if (i-1 >= 0) {
        mi_cell_abajo=&matrix[i-1][j];
        if (mi_cell_abajo->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_abajo=NULL;
      }
      if (j+1 < D) {
        mi_cell_derecha=&matrix[i][j+1];
        if (mi_cell_derecha->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_derecha=NULL;
      }
      if (j-1 >= 0) {
        mi_cell_izquierda=&matrix[i][j-1];
        if (mi_cell_izquierda->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_izquierda=NULL;
      }

      if (i+1 < D && j+1 < D) {
        mi_cell_arribaD=&matrix[i+1][j+1];
        if (mi_cell_arribaD->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_arribaD=NULL;
      }
      if (i-1 >= 0 && j+1 <D) {
        mi_cell_abajoD=&matrix[i-1][j+1];
        if (mi_cell_abajoD->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_abajoD=NULL;
      }
      if (j-1 >= 0 && i+1<D) {
        mi_cell_arribaI=&matrix[i+1][j-1];
        if (mi_cell_arribaI->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_arribaI=NULL;
      }

      if (j-1 >= 0 && i-1>=0) {
        mi_cell_abajoI=&matrix[i-1][j-1];
        if (mi_cell_abajoI->live==1) {
          cercanos ++;
        }
      }
      else{
        mi_cell_abajoI=NULL;
      }

      mi_cell->cercanos=cercanos;
      cercanos=0;
    }
  }
}

void iteracion_tablero(Cell **matrix,int A,int B,int C,int D){
  for(int i=0;i<D;i++){
    for(int j=0;j<D;j++){
      struct cell *mi_cell;
      mi_cell = &matrix[i][j];
      if (mi_cell->live==0) {
        if (mi_cell->cercanos == A){
          mi_cell->live=1;
        }
      }

      else if(mi_cell->live==1){
        if (mi_cell->cercanos > C || mi_cell->cercanos < B){
          mi_cell->live=0;
        }
      }
    }
  }
}

int checkear_vacio(Cell **matrix,int A,int B,int C,int D){
  int vacio = 0;
  for(int i=0;i<D;i++){
    for(int j=0;j<D;j++){
      Cell *cell;
      cell = &matrix[i][j];
      if (cell->live==1) {
        vacio = 1;
      }
    }
  }
  return vacio;
}

int checkear_termino(Stack_Matrix* stack_matrix, Cell **matrix,int A,int B,int C,int D){
  struct mi_mtx actual_mtx;
  struct mi_mtx actual_mtx_next;
  actual_mtx = *stack_matrix->head;
  actual_mtx_next = *actual_mtx.next;
  int result = 1;

  for (size_t i = 0; i < stack_matrix->len; i++) {
    actual_mtx = actual_mtx_next;
    actual_mtx_next = *actual_mtx.next;
    Cell**m;
    m = actual_mtx.matrix;
    for(int i=0;i<D;i++){
      for(int j=0;j<D;j++){
        if(&m[i][j] !=  &matrix[i][j]){
          result = 0;
        }
      }
    }
    if (i==3) {
      break;
    }
  }
}

void print_estados(Stack_Matrix *estados, int D) {
  struct mi_mtx *actual_m;
  struct mi_mtx *actual_m_next;
  actual_m = estados->head;
  actual_m_next = NULL;
  for (int k = 0; k < estados->len; k++) {
    if (actual_m->next != NULL) {
      actual_m_next = actual_m->next;
    }
    printf("estado %d\n\n",k);
    for(int i=0;i<D;i++){
      for(int j=0;j<D;j++){
        printf("%d", actual_m->matrix[i][j]);
      }
      printf("\n");
      }
    printf("\n");
    actual_m = actual_m_next;
    if (actual_m == NULL) {
    break;
    }
  }
}

int checkear_termino_loop(Stack_Matrix* stack_matrix,Cell **matrix, int D){
  struct mi_mtx *actual_m;
  struct mi_mtx *actual_m_next;
  Cell **mtx;
  Cell **mtx2;

  actual_m = stack_matrix->head;
  actual_m_next = NULL;

  int termino = 0;

  for (int k = 0; k < stack_matrix->len; k++){
    int termino2 = 1;
    if (actual_m->next != NULL) {
      actual_m_next = actual_m->next;
    }
    for(int i=0;i<D;i++){
      for(int j=0;j<D;j++){
        mtx = actual_m->matrix;
        mtx2 = matrix;

        if (mtx[i][j].live != mtx2[i][j].live){
          termino2 = 0;
          break;
        }
      }
      if (termino2 == 0) {
        break;
      }
    }
    termino = termino2;
    if (termino == 1){
      break;
      return termino;
    }
    actual_m = actual_m_next;
    if (actual_m == NULL) {
    break;
    }
  }
  return termino;
}
void quit(int sig){
  signal(sig, SIG_IGN);
  printf("Los procesos restantes Terminaron por: SIGNAL\n");
  exit(0);

}

void GameOfLife(Node* tabla,int A,int B,int C,int D, int tiempo_max, FILE *output_file,struct vivas *estado){

  signal(SIGINT,quit);


  Stack_Matrix *estados;
  estados = matrix_init();
  tabla->vivas=0;

  for (size_t i = 0; i < 4; i++) {
    Cell **matrix;
    int i,j;
    int row = D,col = D;

    matrix = (int **) malloc(row*sizeof(struct cell*));
    for(i=0;i<D;i++)
      matrix[i] = (int *) malloc(col*sizeof(struct cell));

    push_mtx(estados, matrix);
  }

  Cell **matrix;
	int i,j;
	int row = D,col = D;

	matrix = (int **) malloc(row*sizeof(struct cell*));
	for(i=0;i<D;i++)
		matrix[i] = (int *) malloc(col*sizeof(struct cell));
/*assigning and printing 2d array*/

	for(i=0;i<D;i++){
		for(j=0;j<D;j++){
			struct cell *mi_cell;
			struct cell *mi_cell2;

			mi_cell = cell_init();
			matrix[i][j] = *mi_cell;
			mi_cell2 =  &matrix[i][j];

		}
	}
  int t = 0;
  crear_tablero(tabla, matrix, D);

  mostrar_tablero(matrix, D, tabla);


  int tiempo_simulacion;
	tiempo_simulacion = 0;


	while (tiempo_simulacion < tiempo_max) {
      contador_celulas(matrix,  tabla,  D);

			checkear_condiciones(matrix,A,B,C,D);
			iteracion_tablero(matrix,  A,  B,  C, D);

       if(tiempo_simulacion == tiempo_max-1){
        contador_celulas(matrix,  tabla,  D);
        printf("m%s Terminó por: NOTIME, tiempo de simulación: %d, %d Celulas \n\n\n",tabla->name,tiempo_simulacion+1, tabla->vivas);
        fprintf(output_file, "%s,%d, %d, NOTIME\n",tabla->name,tiempo_simulacion+1, tabla->vivas);
        break;
			}
      else if (tabla->vivas==0){
        contador_celulas(matrix,  tabla,  D);
        printf("%s Terminó por: NOCELLS, tiempo de simulación: %d, %d Celulas \n\n\n",tabla->name,tiempo_simulacion, tabla->vivas);
        fprintf(output_file, "%s,%d, %d, NOCELLS\n",tabla->name,tiempo_simulacion,  tabla->vivas);
        break;
      }
			else if (checkear_termino_loop(estados, matrix, D)==1) {
        contador_celulas(matrix,  tabla,  D);
				printf("%s Terminó por: LOOP, tiempo de simulación: %d, %d Celulas \n\n\n",tabla->name,tiempo_simulacion+1, tabla->vivas);
        fprintf(output_file, "%s,%d, %d, LOOP\n",tabla->name,tiempo_simulacion+1,  tabla->vivas);
				break;
			}
      else{

    //    mostrar_tablero(matrix, D, tabla);


      }

			guardar_estado(estados, matrix,  A,  B,  C,  D,  tiempo_simulacion);

      tiempo_simulacion++;

	}

}

void contador_celulas(Cell **matrix,Node *tabla, int D){
  tabla->vivas = 0;
  for(int i=0;i<D;i++){
    for(int j=0;j<D;j++){
      Cell *cell;
      cell = &matrix[i][j];
      if (cell->live==1) {
        tabla->vivas++;
      }

    }
  }
}
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}
