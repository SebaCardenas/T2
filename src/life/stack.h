#pragma once
#include <stdio.h>


typedef struct stack Stack;

typedef struct stack_dato Stack_Dato;

typedef struct dato Dato;

typedef struct node Node;

typedef struct cell Cell;

typedef struct stack_matrix Stack_Matrix;

static int *glob_var;

struct cell
{
  int live;
  int cercanos;
};

struct node
{
  char *name;
  int ID;
  struct node *next;
  struct stack_dato *dato;
  int vivas;
};

struct stack
{
  struct node *head;
  int len;
};

struct stack_matrix
{
  struct mi_mtx *head;
  int len;
};

struct mi_mtx
{
  struct mi_mtx *next;
  Cell **matrix;
};

struct stack_dato
{
  struct dato *head;
  struct dato *tail;
  int len;
};

struct dato
{
  int posicion;
  struct dato *next;
};

struct vivas{
  int live;
};

Stack *stack_init();

Stack_Matrix *matrix_init();

Stack_Dato *stack_dato_init();

Cell *cell_init();
/*
struct stack *search_stack(int **matrix,int p_row,int p_column);
*/
void push(Stack* stack,Stack_Dato* stack_dato, char *name, int id);



void push_mtx(Stack_Matrix* stack_matrix, Cell **matrix);

void push_dato(Stack_Dato* stack_dato, int posicion);

void crear_tablero(Node * tablero, Cell **matrix,int D);

void mostrar_tablero(Cell **matrix, int D, Node* tabla);

void resetear_tablero(Cell ** matrix, int D);

void checkear_condiciones(Cell ** matrix,int A, int B, int C, int D);

void iteracion_tablero(Cell **matrix,int A,int B,int C,int D);

int checkear_vacio(Cell **matrix,int A,int B,int C,int D);

int checkear_termino(Stack_Matrix* stack_matrix,Cell **matrix,int A,int B,int C,int D);

void guardar_estado(Stack_Matrix* stack_matrix, Cell **matrix,int A,int B,int C,int D, int tiempo_simulacion);

void print_estados(Stack_Matrix *estados, int D) ;

void quit(int sig);

int checkear_termino_loop(Stack_Matrix* stack_matrix,Cell **matrix, int D);

void GameOfLife(Node* tabla,int A,int B,int C,int D,int tiempo_max, FILE* output_file, struct vivas *estado);

void contador_celulas(Cell **matrix,Node *tabla,int D);

int pop(Stack_Dato* stack);

void destroy(Stack *stack);

int random_number(int min_num, int max_num);
