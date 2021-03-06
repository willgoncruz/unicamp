/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "colored.h"

/* Implementação dos métodos */

int insertColoredDollOnList (Doll * doll, List ** list) {
	Colored * newColored = createColored(doll),
			* colored;

	Node * newNode = createNode((void*) newColored),
		 * actual,
		 * previous;

	if (blank(list)) {
		(*list)->first = newNode;
		return SUCESS_COLORING;
	}

	previous = (*list)->first;
	colored = (Colored*) previous->value;

	/* Cobrindo os casos para o primeiro elemento da lista */
	if (sameNumberDifferentColor(colored, newColored)) {
		return ERROR_COLORING;
	}

	if (colored->number > newColored->number) {
		newNode->next = previous;
		(*list)->first = newNode;
		return SUCESS_COLORING;
	}

	if (colored->number == newColored->number) {
		return SUCESS_COLORING;
	}

	for (actual = previous->next; actual != NULL;) {
		colored = (Colored*) actual->value;

		/* Cobrindo os casos para cada elemento da lista */
		if (sameNumberDifferentColor(colored, newColored)) {
			return ERROR_COLORING;
		}

		if (colored->number == newColored->number) {
			return SUCESS_COLORING;
		}

		/* Chegando a posição onde o número ordenado deveria estar */
		if (colored->number > newColored->number) {
			break;
		}

		previous = actual;
		actual = actual->next;
	}

	newNode->next = actual;
	previous->next = newNode;

	return SUCESS_COLORING;
}

Colored * createColored (Doll * doll) {
	Colored * colored = malloc(sizeof(Colored));
	colored->number = doll->number;
	colored->color = doll->color;
	return colored;
}

bool sameNumberDifferentColor (Colored * colored, Colored * new) {
	if (colored->number != new->number) {
		return false;
	}

	if (colored->color == new->color) {
		return false;
	}

	return true;
}

void response (List ** list) {
	Node * actual;
	Colored * colored;
	printf("%s", SUCESS_MESSAGE);

	for (actual = (*list)->first; actual != NULL; actual = actual->next) {
		colored = (Colored*) actual->value;
		printf("%d: ", colored->number);

		switch (colored->color) {
			case RED:
				printf("vermelho\n");
				break;
			case BLUE:
				printf("azul\n");
				break;
			default:
				break;
		}
	}
}