/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

/* Implementação dos métodos */

void readAllClientRequests(Tree * ingredients) {
	String ingredientName;
	int clockTime,
		sequential,
		overflowTimeTotal = 0,
		overflowTimeIngredient = 0;

	List * waitingList = createList();

	sequential = 1;
	while (scanf("%d", &clockTime) == 1) {
		Client * client = createClient(sequential);

		while (scanf("%*[ ]%[^ \r\n]", ingredientName) == 1) {
			// TODO ver alocação das porções de ingredientes

			overflowTimeIngredient = availabilityOfIngredient(ingredients, ingredientName, clockTime);

			if (overflowTimeIngredient > overflowTimeTotal) {
				overflowTimeTotal = overflowTimeIngredient;
			}
		}

		if (overflowTimeTotal) {
			overflow(&client, overflowTimeTotal);
			insertTail(&waitingList, client);
			// TODO retirar alguém da lista de espera para assar
		} else {

		}

		sequential++;
	}
}