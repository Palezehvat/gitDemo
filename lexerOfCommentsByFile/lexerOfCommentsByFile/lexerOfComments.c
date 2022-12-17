#include "lexerOfComments.h"

int changeStage(int statusTable[5][2], int stage, int symbol) {
	int posSymbol = symbol % 42 == 0 ? 0 : 1;
	return statusTable[stage][posSymbol];
}

void clearBuffer(char buffer[], int* index) {
	memset(buffer, 0, strlen(buffer));
	*index = 0;
}

char* workWithStage(int statusTable[5][2], const char* fileNameWithStrings, Error* errorCheck) {
	FILE* file = fopen(fileNameWithStrings, "r");
	if (file == NULL) {
		*errorCheck = fileProblem;
		return NULL;
	}
	char symbol = 0;
	char bufferWithOneComment[1000] = { '\0' };
	char bufferWithAllComments[10000] = { '\0' };
	int stage = 1;
	int indexBuffer = 0;
	while (fscanf(file, "%c", &symbol) == 1) {
		if (symbol == '/') {
			switch (stage) {
			case(1):
				if (indexBuffer == 0) {
					bufferWithOneComment[indexBuffer] = '/';
					++indexBuffer;
				}
				break;
			case(2):
				clearBuffer(bufferWithOneComment, &indexBuffer);
				bufferWithOneComment[0] = '/';
				indexBuffer = 1;
				break;
			case(3):
				bufferWithOneComment[indexBuffer] = symbol;
				++indexBuffer;
				break;
			case(4):
				bufferWithOneComment[indexBuffer] = symbol;
				++indexBuffer;
				strcat(bufferWithAllComments, bufferWithOneComment);
				memset(bufferWithOneComment, 0, strlen(bufferWithOneComment));
				indexBuffer = 0;
				break;
			}
			stage = changeStage(statusTable, stage, (int)symbol);
		} else if (symbol == '*') {
			switch (stage) {
			case(1):
				clearBuffer(bufferWithOneComment, &indexBuffer);
				break;
			case(2):
				bufferWithOneComment[indexBuffer] = symbol;
				++indexBuffer;
				break;
			case(3):
				bufferWithOneComment[indexBuffer] = symbol;
				++indexBuffer;
				break;
			case(4):
				clearBuffer(bufferWithOneComment, &indexBuffer);
				break;
			}
			stage = changeStage(statusTable, stage, (int)symbol);
		} else {
			if (stage == 3) {
				bufferWithOneComment[indexBuffer] = symbol;
				++indexBuffer;
			} else {
				clearBuffer(bufferWithOneComment, &indexBuffer);
				stage = 1;
			}
		}
	}
	fclose(file);
	return bufferWithAllComments;
}

char* lexerOfComments(const char* fileNameTable, const char* fileNameWithStrings, Error* errorCheck) {
	FILE* file = fopen(fileNameTable, "r");
	if (file == NULL) {
		*errorCheck = fileProblem;
		return NULL;
	}
	int statusTable[5][2] = { 0 };
	char expression[3] = { '\0' };
	if (fscanf(file, "%s", expression) == 1) {
		statusTable[0][0] = expression[0];
		statusTable[0][1] = expression[1];
	}

	for (int i = 1; i < 5; ++i) {
		if (fscanf(file, "%s", expression) == 1) {
			statusTable[i][0] = expression[0] - 48;
			statusTable[i][1] = expression[1] - 48;
		}
	}
	fclose(file);

	return workWithStage(statusTable, fileNameWithStrings, errorCheck);
}