/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "cache.h"

/* Implementação dos métodos */

Cache * createCache(int number, int priority) {
	Cache * cache = malloc(sizeof(Cache));
	cache->number = number;
	cache->priority = priority;
	cache->isCached = NOT_CACHED;

	cache->appearances = createList();
	cache->appearances->head = cache->appearances->tail = createNodeList(priority);

	return cache;
}

int compare(Cache * first, Cache * second) {
	if (first->priority == NO_NEXT_APPEARANCE) {
		return GREATER;
	}

	if (second->priority == NO_NEXT_APPEARANCE) {
		return LESSER;
	}

	if (first->priority <= second->priority) {
		return LESSER;
	}

	return GREATER;
}

int compareNumber(Cache * first, Cache * second) {
	if (first->number > second->number) {
		return GREATER;
	}

	if (first->number < second->number) {
		return LESSER;
	}

	return EQUALS;
}

void updatePriority(Cache * cache, int position) {
	cache->priority = findNextAppearance(&cache->appearances, position);
}

void freeCache(Cache ** cache) {
	freeList(&(*cache)->appearances);
	free(*cache);
}