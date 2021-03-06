/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "list.h"

/* Implementação dos métodos da lista */

Node * createNode(int key) {
	Node * node = malloc(sizeof(Node));
	node->key = key;
	node->next = NULL;
	return node;
}

void init(List ** list, int transpositionValue) {
	(*list) = malloc(sizeof(List*));
	(*list)->first = NULL;
	(*list)->allCosts = 0;
	(*list)->transpositionValue = transpositionValue;
}

void insert(int key, List ** list) {
	Node * new = createNode(key),
		 * actual;

	// O custo de uma inserção em lista não vazia nesse algoritmo começa em 2
	int cost = 2;

	if ((*list)->first == NULL) {
		(*list)->first = new;
		(*list)->allCosts++;
		return;
	}

	for (actual = (*list)->first; actual->next != NULL; cost++) {
		actual = actual->next;
	}

	actual->next = new;
	(*list)->allCosts += cost;

	/* Faz a transposição entre o anterior e o próximo caso seja a lista
	 * Em formato TR */
	if ((*list)->transpositionValue == TR) {
		transposition(&actual, &actual->next);
	}
}

void find(int key, List ** list) {
	Node * actual,
		 * previous;

	int cost = 1;

	previous = NULL;
	actual = (*list)->first;

	for (; actual != NULL; cost++) {
		if (actual->key == key) {
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	// Faz a transposição dependendo do formato da lista em que se foi buscado
	if ((*list)->transpositionValue == TR) {
		transposition(&previous, &actual);
	} else if ((*list)->transpositionValue == MTF) {
		transpositionListFirst(list, &previous, &actual);
	}

	(*list)->allCosts += cost;
}

void removeList(int key, List ** list) {
	Node * actual,
		 * previous;

	// O custo de uma remoção em lista não vazia nesse algoritmo começa em 2
	int cost = 2;

	if ((*list)->first->key == key) {
		actual = (*list)->first;
		(*list)->first = actual->next;
		free(actual);
		(*list)->allCosts++;
		return;
	}

	previous = (*list)->first;
	actual = previous->next;

	for (; actual != NULL; cost++) {
		if (actual->key == key) {
			previous->next = actual->next;
			free(actual);
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	(*list)->allCosts += cost;
}

void copy(List ** original, List ** copy) {
	Node * actual;
	for (actual = (*original)->first; actual != NULL; actual = actual->next) {
		insert(actual->key, copy);
	}

	// Reinicializa a copia, pois não há importancia para elementos iniciais
	(*copy)->allCosts = 0;
}

void transposition(Node ** previous, Node ** actual) {
	// Caso o atual seja o primeiro da lista, não há transposição
	if (*previous == NULL) {
		return;
	}

	// Troca as chaves dos nós apenas, não seus ponteiros
	int aux = (*previous)->key;
	(*previous)->key = (*actual)->key;
	(*actual)->key = aux;
}

void transpositionListFirst(List ** list, Node ** previous, Node ** actual) {
	// Caso o atual seja o primeiro da lista, não há transposição
	if (*previous == NULL) {
		return;
	}

	// Troca os ponteiros para colocar o atual em primeiro
	(*previous)->next = (*actual)->next;
	(*actual)->next = (*list)->first;
	(*list)->first = (*actual);
}

void freeNodes(Node * node) {
	if (node == NULL) {
		return;
	}

	freeNodes(node->next);
	free(node);
}

void freeList(List ** list) {
	freeNodes((*list)->first);
	free((*list));
}