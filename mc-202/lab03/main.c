/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "reading.h"

int main() {
	Doll * outsided;

	createDollsRelation(&outsided);

	if (outsided == NULL) {
		printf("%s", ERROR_MESSAGE);
	}

	freeDolls(outsided);

	return 0;
}