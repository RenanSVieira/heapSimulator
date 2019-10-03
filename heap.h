#include <stdio.h>
#include <stdlib.h>

#define N 10

int nex;

typedef struct lista Lista;
//
void printa_lista_o(Lista *l);

void printa_lista_v(Lista *l);

void printa_lista(Lista *l);

void inserir_fim(Lista *l, int end, int tam, int id);

Lista *addElemento(Lista *l, int id, int end, int tam);

Lista *preenche_lista(int *heap);

//

void ler_heap(FILE *f, int *heap);

void printa_heap(int *heap);

Lista *remover_lista(int end, int *heap,  Lista *inicio);

Lista *preenche_heap(Lista *l, int *heap);

int achar_nex(Lista *inicio, Lista *l);

Lista *inserir_heap(Lista *l,Lista *inicio, int *v, int tam);

Lista *next_fit(Lista *l, int *v, int tam);

Lista *worst_fit(Lista *l, int *v, int tam);

Lista *best_fit(Lista *l, int *v, int tam);

Lista *first_fit(Lista *l, int *v, int tam);




