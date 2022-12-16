#include "lexerOfComments.h"

/*

Типы символов:
0 Открытие комментария если встретили / -> переходим к следущей стадии1.
1 Проверка на наличие * -> переход к последовательности символов 2. Если есть / переводим в 1. Если нет переходим к стадии 0.
2 Сканирование символов. Проверка на наличие * -> переход к следущей стадии 3. Если нет *, но есть / переход к стадии 1. Иначе переходим к стадии 0.
? Может ли 1 / принадлежать двум комментариям ? 
3 Если есть / Сохраняем комментарий. Переходим к стадии 0.


   stage * / 
	 0	 0 1
	 1	 2 1
	 2   3 1
	 3   0 0
*/

char* workWithStage(int statusTable[4][3], const char* fileNameWithStrings, Error* errorCheck) {
	FILE* file = fopen(fileNameWithStrings, "r");
	if (file == NULL) {
		*errorCheck = fileProblem;
		return NULL;
	}
	char symbol = 0;
	char bufferWithOneComment[10000] = { '\0' };
	char bufferWithAllComments[100000] = { '\0' };
	int stage = 0;
	while (fscanf_s(file, '%c', &symbol) == 1) {
		if ()
	}

	return bufferWithAllComments;
}

char* lexerOfComments(const char* fileNameTable, const char* fileNameWithStrings, Error* errorCheck) {
	FILE* file = fopen(fileNameTable, "r");
	if (file == NULL) {
		*errorCheck = fileProblem;
		return NULL;
	}
	int statusTable[4][3] = { 0 };
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			int changeStage = 0;
			if (fscanf_s(file, '%d', &changeStage) == 1) {
				statusTable[i][j] = changeStage;
			}
		}
	}

	return workWithStage(, fileNameWithStrings, errorCheck);
}