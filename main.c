#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "heap.h"

///first best worst next

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FILE *f = fopen("heap.txt","r");
        if(f == NULL) exit(1);

    Lista *l;
    int *heap = (int*)malloc(N*sizeof(int));
    int op1, op2, tam, del;

    ler_heap(f,heap);
    l = preenche_lista(heap);

    while(1)
    {
        fflush(stdin);
        printf("nex = %d\n\n", nex);
        printf("Escolha a opção desejada:\n\n");
        printf("1 - Visualizar heap:\n");
        printf("2 - Visualizar listas (espaços vazios/ocupados):\n");
        printf("3 - adicionar elemento:\n");
        printf("4 - Remover elemento:\n");
        printf("5 - Sair\n");

        scanf("%d", &op1);

        switch(op1)
        {
        case 1:
            printf("\n\n");
            printa_heap(heap);
            printf("\n\n");
            printa_lista(l);
            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 2:
            printf("\n\n");
            printa_heap(heap);
            printa_lista_o(l);
            printa_lista_v(l);
            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            printf("nex = %d\n\n", nex);
            printf("Digite a opção desejada:\n\n");
            printf("1 - first fit:\n");
            printf("2 - best fit:\n");
            printf("3 - worst fit:\n");
            printf("4 - next fit:\n");
            printa_heap(heap);
            scanf("%d", &op2);


            printf("\n\n");
            printf("Digite o tamanho:\n");
            scanf("%d", &tam);

            switch(op2)
            {
            case 1:
                l = first_fit(l,heap,tam);

                printa_heap(heap);
                printf("\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                l = best_fit(l,heap,tam);

                printa_heap(heap);
                printf("\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                l = worst_fit(l,heap,tam);

                printa_heap(heap);
                printf("\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                l = next_fit(l,heap,tam);

                printa_heap(heap);
                printf("\n\n");
                system("pause");
                system("cls");
                break;
            }
            break;
        case 4:
            printa_lista_o(l);

            printf("Escolha o inicio do endereço de onde deseja remover:\n");
            scanf("%d", &del);

            l = remover_lista(del,heap,l);

            printa_heap(heap);

            system("pause");
            system("cls");

            break;
        case 5:
            exit(1);
            break;
        default:
            system("cls");
            break;
        }
    }

    return 0;
}
