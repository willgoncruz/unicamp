/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "heap.h"

/* Implementação dos métodos */

Heap * createHeap(int size) {
	Heap * heap = malloc(sizeof(Heap));
	heap->maxSize = size;
	heap->actualSize = ZERO_INIT;

	// Inicializa o vetor de cache com elementos vazios
	heap->data = malloc(size * sizeof(Cache*));
	for (int i = ZERO_INIT; i < size; i++) {
		heap->data[i] = NULL;
	}

	return heap;
}

int isFull(Heap * heap) {
	return (heap->actualSize == heap->maxSize);
}

int parent(int position) {
	return (position - 1) / 2;
}

void heapify(Heap * heap, int progress) {
	Heap * newHeap = malloc(sizeof(newHeap));
	newHeap->data = malloc(heap->actualSize * sizeof(Cache*));

	// Aplica a alteração de prioridade e rebalanceamento para cada elemento
	for (int i = 0; i < heap->actualSize; i++) {
		newHeap->data[i] = heap->data[i];
		updatePriority(newHeap->data[i], progress);
		shiftUp(newHeap, i);
	}

	// Libera espaco da antiga heap e realoca com a nova
	free(heap->data);
	heap->data = newHeap->data;
	free(newHeap);
}

int storeCache(Heap * heap, Tree * tree, int cacheNumber, int progress) {
	Cache * searched = search(tree->root, cacheNumber);

	// Caso o elemento já esteja na heap, retorna que não houve alterações
	if (searched->isCached) {
		return NO_CACHE_CHANGE;
	}

	searched->isCached = IS_CACHED;

	// Caso o heap esteja cheio, remove o maior (raiz) e diminue o tamanho
	if (isFull(heap)) {
		heapify(heap, progress);
		heap->data[0]->isCached = NOT_CACHED;
		heap->data[0] = heap->data[heap->actualSize - 1];
		heap->actualSize--;
	}

	// Caso geral, insere na última posição possível
	heap->actualSize++;
	heap->data[heap->actualSize - 1] = searched;

	return CACHE_CHANGED;
}

void shiftUp(Heap * heap, int position) {
	int comparison,
		parentPos = parent(position);

	// Caso seja a raiz, não possue pai
	if (!position) {
		return;
	}

	// Compara a posição atual com seu pai e os troca caso o pai seja menor do que o filho
	comparison = compare(heap->data[parentPos], heap->data[position]);

	if (comparison == LESSER) {
		exchange(heap, parentPos, position);
		shiftUp(heap, parentPos);
	}
}

void exchange(Heap * heap, int first, int second) {
	Cache * tmp = heap->data[first];
	heap->data[first] = heap->data[second];
	heap->data[second] = tmp;
}

void freeHeap(Heap ** heap) {
	free((*heap)->data);
	free(*heap);
}