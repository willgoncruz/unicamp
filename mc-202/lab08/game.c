/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

int isStringEnd(char c) {
	return (c == ' ') || (c == '\n');
}

void clearString(String s) {
	memset(s, 0, MAX_WORD_SIZE);
}

void readString(String s) {
	char c;
	for (int i = 0; ; i++) {
		scanf("%c", &c);
		if (isStringEnd(c)) {
			break;
		}

		s[i] = c;
	}
}

void readInt(int * i) {
	scanf("%d ", i);
}

void readLongInt(unsigned long * ul) {
	scanf("%lu ", ul);
}

int min(int a, int b) {
	return (a > b) ? b : a;
}

void applyPlay(HashTable * table, Player * players, int playerCount) {
	int phraseCount,
		phraseSequenceCount,
		score,
		hasHit,
		count;

	long oldScores[playerCount];
	String actual;

	Word * word = NULL,
		 * playerTry = NULL,
		 * previous = NULL;

	// Grava o estado do placar antes da rodada acontecer
	backup(oldScores, players, playerCount);

	readInt(&phraseCount);
	clearString(actual);
	readString(actual);

	/* Aloca o começo da frase e inicializa a variável de miníma ocorrência */
	word = search(table, actual);
	phraseSequenceCount = table->size;

	for (phraseCount--; phraseCount > 0; phraseCount--) {
		previous = word;

		clearString(actual);
		readString(actual);

		// Find ajdacency on next and previous words
		word = search(table, actual);
		count = find(&word->adjacencies, previous, NULL);

		// Atualiza a contagem da frase com a contagem da adjacência entre as palavras
		phraseSequenceCount = min(phraseSequenceCount, count);
	}

	hasHit = NO_HIT;

	for (int i = 0; i < playerCount; i++) {
		// Para cada jogador, lê o palpite e avalia a jogada
		clearString(actual);
		readString(actual);

		playerTry = search(table, actual);

		// Caso foi um palpite errado do jogador, e a palavra nem existe no texto, logo ele perde pontos
		if (!playerTry) {
			score = min(phraseSequenceCount, word->afterCount);
			miss(&players[i], score);
			continue;
		}

		count = find(&word->adjacencies, previous, playerTry);

		if (count) {
			// Caso haja adjacência, o palpite foi correto e o jogador deve marcar pontos
			score = min(phraseSequenceCount, count);
			hit(&players[i], score);
			hasHit = HIT;
		} else {
			// Caso contrário, foi um palpite errado do jogador, a palavra existe no texto logo ele perde pontos
			score = min(phraseSequenceCount, word->afterCount);
			miss(&players[i], score);
		}
	}

	// Caso ninguém tenha acertado, volta o placar para como era no começo da rodada
	if (!hasHit) {
		restore(oldScores, players, playerCount);
	}
}