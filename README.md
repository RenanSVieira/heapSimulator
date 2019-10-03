# heapSimulator

Um programa feito para simular uma memória heap

ele lê de um arquivo com '0's e '1's e transfere as informações para um vetor "heap" e uma lista encadeada que agora contém as informações do heap:

#id = diz se esse espaço está vazio (0) ou ocupado (1) na memória

#end = endereço de início

#tam = tamanho do espaço

O programa disponibiliza opções para visualizar o heap/lista, adicionar e remover conteúdo no heap.

Ao visualizar as listas, você receberá vários pares de números aos quais indicam, respectivamente, o endereço de início do conteúdo e o seu tamanho na memória.

4 estratégias estão disponíveis ao adicionar conteúdo no heap:

first fit --> a partir do início do heap, adiciona o conteúdo desejado no primeiro espaço disponível.

best fit --> adiciona o conteúdo no espaço de memória em que haverá o menor "desperdício" de memória possível, tentando sempre encaixar no espaço em que ele encaixe perfeitamente sempre que possível.

worst fit --> adiciona o conteúdo no espaço de memória em que haverá o maior "desperdício" de memória possível, tentando sempre deixar o maior espaço vazio sobrando na memória.

next fit --> a partir do último endereço adicionado anteriormente, adiciona o conteúdo desejado no primeiro espaço disponível.
