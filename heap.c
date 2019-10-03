#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

nex = 0;

typedef struct lista{
    int id;                 ///0 == vazia - 1 == cheia
    int end;
    int tam;
    struct lista *prox;
}Lista;

void ler_heap(FILE *f, int *heap)
{
    char n;
    char lixo;
    int i = 0;

    for(n = fgetc(f); n != EOF; n = fgetc(f))
    {
        if(n == '0')
            heap[i] = 0;
        else if(n == '1')
            heap[i] = 1;

        lixo = fgetc(f);
        i++;
    }
}

void printa_heap(int *heap)
{
    printf("HEAP -> ");
    for(int i = 0; i < N; i++)
        printf("[%d] ", heap[i]);
    printf("\n\n");
}

Lista *remover_lista(int end, int *heap,  Lista *inicio)
{
    Lista *aux = inicio;
    Lista *ant = NULL;

    while(aux != NULL && aux->end != end)
    {
        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL || aux->id == 0)
        return inicio;

    for(int i = 0; i < aux->tam; i++)
    {
        heap[aux->end + i] = 0;
    }

    if(ant == NULL)
    {
        aux->id = 1;
        return inicio;
    }
    else if(ant != NULL)
    {
        if(ant->id == 0)
        {
            ant->tam = ant->tam + aux->tam;
        }
        else if(ant->id == 1)
        {
            aux->id = 0;
            if(aux->prox != NULL && aux->prox->id == 1)
                return inicio;
            else if(aux->prox != NULL && aux->prox->id == 0)
            {
                aux->prox->tam += aux->tam;
                aux->prox->end = aux->end;
                ant->prox = aux->prox;
                free(aux);
                return inicio;
            }
            else if(aux->prox == NULL)
            {
                return inicio;
            }
        }

        if(aux->prox != NULL)
        {
            if(aux->prox->id == 0)
            {
                ant->tam = ant->tam + aux->prox->tam;
                ant->prox = aux->prox->prox;
            }
            else if(aux->prox->id != 0)
                ant->prox = aux->prox;
        }
        else if(aux->prox == NULL)
        {
            ant->prox = NULL;
        }
    }

    free(aux);

    return inicio;
}

Lista *preenche_heap(Lista *l, int *heap)
{
    Lista *inicio = l;
    int i;

    while(l != NULL)
    {
        if(l->id == 0)
        {
            for(i = l->end; i < (l->end + l->tam); i++)
                heap[i] = 0;
        }
        else if(l->id == 1)
        {
            for(i = l->end; i < (l->end + l->tam); i++)
                heap[i] = 1;
        }

        l = l->prox;
    }

    return inicio;
}

int achar_nex(Lista *inicio, Lista *l)
{
    Lista *aux = l;
    int verifica = 0;

    while(aux != NULL)
    {
        if(verifica == 1 && aux->end == l->end)
        {
            printf("Não há espaço\n");
            break;
        }
        if(aux->id == 0)
        {
            return aux->end;
        }

        aux = aux->prox;

        if(aux == NULL)
        {
            verifica = 1;
            aux = inicio;
        }
    }
}

Lista *inserir_heap(Lista *l,Lista *inicio, int *v, int tam)
{
    int i;
    Lista *ant = NULL;
    Lista *aux = inicio;
    Lista *novo = (Lista*)malloc(sizeof(Lista));

    novo->id = 1;
    novo->end = l->end;
    novo->tam = tam;

    for(i = 0; i < tam; i++)
    {
        v[l->end + i] = 1;
    }

    while(aux != NULL && aux->end != l->end)
    {
        ant = aux;
        aux = aux->prox;
    }

    l->end = l->end + tam;
    l->tam = l->tam - tam;

    if(l->tam == 0)
    {
        if(ant != NULL)
        {
            ant->prox = novo;
            novo->prox = l->prox;
            free(l);
            nex = achar_nex(inicio,novo->prox);
        }
        else
        {
            novo->prox = l->prox;
            free(l);
            nex = achar_nex(inicio,novo->prox);
            return novo;
        }
    }
    else
    {
        if(ant != NULL)
        {
            ant->prox = novo;
            novo->prox = l;
            nex = achar_nex(inicio,l);
        }
        else
        {
            novo->prox = l;
            nex = l->end;
            nex = achar_nex(inicio,l);
            return novo;
        }
    }

    return inicio;
}

Lista *next_fit(Lista *l, int *v, int tam)
{
    Lista *inicio = l;
    int verifica = 0;

    while(l != NULL)
    {
        if(l->end == nex)
            break;
        else
            l = l->prox;
    }

    if(l->tam >= tam)
    {
        l = inserir_heap(l,inicio,v,tam);
        return l;
    }
    else
        l = l->prox;


    while(l == NULL || l->end != nex)
    {
        if(l == NULL && verifica == 0)
        {
            l = inicio;
            verifica = 1;
        }
        if(l->end == nex)
            break;

        if(l->tam >= tam)
        {
            l = inserir_heap(l,inicio,v,tam);
            return l;
        }
        else
        {
            l = l->prox;
        }
    }

    printf("não há espaço o suficiente no heap!");

    return inicio;
}

Lista *worst_fit(Lista *l, int *v, int tam)
{
    Lista *inicio = l;
    Lista *worst = NULL;
    int worst_tam = 0;

    while(l != NULL)
    {
        if(l->id == 0)
        {
            if(l->tam >= tam)
            {
                if((l->tam - tam) > worst_tam)
                {
                    worst_tam = (l->tam - tam);
                    worst = l;
                }
            }
        }
        l = l->prox;
    }

    l = inicio;

    if(worst != NULL)
    {
        l = inserir_heap(worst,inicio,v,tam);
        return inicio;
    }

    printf("não há espaço o suficiente no heap!");

    return inicio;
}

Lista *best_fit(Lista *l, int *v, int tam)
{
    Lista *inicio = l;
    Lista *best = NULL;
    int best_tam = N;

    while(l != NULL)
    {
        if(l->id == 0)
        {
            if(l->tam >= tam)
            {
                if((l->tam - tam) < best_tam)
                {
                    best_tam = (l->tam - tam);
                    best = l;
                }
            }
        }
        l = l->prox;
    }

    l = inicio;

    if(best != NULL)
    {
        l = inserir_heap(best,inicio,v,tam);
        return inicio;
    }

    printf("não há espaço o suficiente no heap!");

    return inicio;
}

Lista *first_fit(Lista *l, int *v, int tam)
{
    Lista *inicio = l;

    while(l != NULL)
    {
        if(l->tam >= tam && l->id == 0)
        {
            l = inserir_heap(l,inicio,v,tam);

            return l;
        }
        else
            l = l->prox;
    }

    printf("não há espaço o suficiente no heap!");

    return inicio;
}

void printa_lista_o(Lista *l)
{
    Lista *l_aux = l;

    printf("LISTA OCUPADA-> ");

    while(l_aux != NULL)
    {
        if(l_aux->id == 1)
        {
            printf("[%d %d] ", l_aux->end, l_aux->tam);
        }
        l_aux = l_aux->prox;
    }
    printf("\n");
}

void printa_lista_v(Lista *l)
{
    Lista *l_aux = l;

    printf("LISTA VAZIA-> ");

    while(l_aux != NULL)
    {
        if(l_aux->id == 0)
        {
            printf("[%d %d] ", l_aux->end, l_aux->tam);
        }
        l_aux = l_aux->prox;
    }
    printf("\n");
}

void printa_lista(Lista *l)
{
    Lista *l_aux = l;

    printf("LISTA -> ");

    while(l_aux != NULL)
    {
        printf("[%d %d] ", l_aux->end, l_aux->tam);

        l_aux = l_aux->prox;
    }
    printf("\n");
}

void inserir_fim(Lista *l, int end, int tam, int id)
{
    if(l!=NULL)
    {
        Lista *novo = (Lista*)malloc(sizeof(Lista));
        novo->id = id;
        novo->end = end;
        novo->tam = tam;
        novo->prox = NULL;

        if(l->prox == NULL)
        {
            l->prox = novo;
        }
        else
        {
            Lista *aux = l;
            while(aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
    else
    {
        Lista *novo = (Lista*)malloc(sizeof(Lista));
        novo->id = id;
        novo->end = end;
        novo->tam = tam;
        novo->prox = NULL;
    }
}

Lista *addElemento(Lista *l, int id, int end, int tam)
{
    Lista *inicio = l;
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->id = id;
    novo->end = end;
    novo->tam = tam;
    novo->prox = NULL;

    if(l != NULL)
    {
        while(l->prox != NULL)
        {
            l = l->prox;
        }

        l->prox = novo;

        return inicio;
    }
    else
    {
        return novo;
    }
}

Lista *preenche_lista(int *heap)
{
    int i;
    int cont = 1;
    int aux = heap[0];
    int end = 0;

    Lista *l = NULL;

    for(i = 1; i < N; i++)
    {
        if(heap[i] == heap[i-1])
        {
            cont += 1;
        }
        else
        {
            l = addElemento(l,heap[i-1],end,cont);
            cont = 1;
            end = i;
        }
    }

    l = addElemento(l,heap[i-1],end,cont);

    return l;
}
