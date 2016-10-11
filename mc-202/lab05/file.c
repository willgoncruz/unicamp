/* Nome  : William Gonçalves da Cruz
 * RA    : 188671
 * Turma : F
 */

#include "file.h"

/* Implementação dos métodos */

File* createFile(String name) {
	File * f = malloc(sizeof(File));
	f->count = INITIAL_COUNT;
	strcpy(f->name, name);
	return f;
}

void increase(File ** file) {
	(*file)->count++;
}

int compareFiles(File * first, File * second) {
	return strcmp(first->name, second->name);
}

int isPrefixExpression(File * file, String expression) {
	for (int i = 0; expression[i] != STRING_END; i++) {
		if (expression[i] == REGEX_LETTER) {
			return EQUALS;
		}

		if (file->name[i] == STRING_END) {
			return LESSER;
		}

		if (file->name[i] < expression[i]) {
			return LESSER;
		}

		if (file->name[i] > expression[i]) {
			return HIGHER;
		}
	}

	return EQUALS;
}

void freeFile(File ** file) {
	free(*file);
}