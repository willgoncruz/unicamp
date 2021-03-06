/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "word.h"

/* Implementação dos métodos */

Word* createWord(String id) {
	Word * word = malloc(sizeof(Word));
	word->adjacencies = createList();
	word->hash = ZERO_INIT;
	word->afterCount = ZERO_INIT;
	strcpy(word->id, id);
	return word;
}

int compare(String first, String second) {
	return strcmp(first, second);
}

int compareWords(Word * first, Word * second) {
	return (first->hash == second->hash);
}

void raiseAfterCount(Word ** word) {
	(*word)->afterCount++;
}

void freeWord(Word ** word) {
	freeList(&(*word)->adjacencies);
	free(*word);
}