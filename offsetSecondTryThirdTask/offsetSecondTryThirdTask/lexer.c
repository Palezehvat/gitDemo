#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum Stage {
	first,
	second,
	third,
	fourth,
	fifth
} Stage;

char* workWithFileAndReturnString(const char* nameFile, Error* errorCheck) {
	FILE* file = fopen(nameFile, "r");
	if (file == NULL) {
		*errorCheck = errorWithFile;
		return NULL;
	}
	char buffer[1000] = { '\0' };
	char result[10000] = { '\0' };
	Stage stage = first;
	char symbol = 0;
	int indexBuffer = 0;
	bool isNeedAddLast = false;
	while (fscanf(file, "%c", &symbol) == 1) {
		switch (stage)
		{
		case first:
			if (symbol >= 'A' && symbol <= 'Z' || symbol == '+' || symbol == '-'
				|| symbol >= '0' && symbol <= '9' || symbol == '.' || symbol == '%') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = first;
			}
			else if (symbol == '@') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = second;
			}
			else {
				memset(buffer, 0, strlen(buffer));
				indexBuffer = 0;
				stage = first;
			}
			break;
		case second:
			if (symbol >= 'A' && symbol <= 'Z'
				|| symbol >= '0' && symbol <= '9' || symbol == '-') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = third;
			} else {
				memset(buffer, 0, strlen(buffer));
				indexBuffer = 0;
				stage = first;
			}
			break;
		case third:
			if (symbol >= 'A' && symbol <= 'Z'
				|| symbol >= '0' && symbol <= '9' || symbol == '-') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = third;
			}
			else if (symbol == '.') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = fourth;
			}
			else {
				memset(buffer, 0, strlen(buffer));
				indexBuffer = 0;
				stage = first;
			}
			break;
		case fourth:
			if (symbol >= 'A' && symbol <= 'Z') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = fifth;
				isNeedAddLast = true;
			} else if (symbol >= '0' && symbol <= '9' || symbol == '-') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = third;
			} else {
				memset(buffer, 0, strlen(buffer));
				indexBuffer = 0;
				stage = first;
			}
			break;
		case fifth:
			if (symbol >= '0' && symbol <= '9' || symbol == '-' || symbol == '.') {
				buffer[indexBuffer] = symbol;
				++indexBuffer;
				stage = fourth;
				isNeedAddLast = false;
				break;
			} else {
				strcat(result, buffer);
				memset(buffer, 0, strlen(buffer));
				indexBuffer = 0;
				if (symbol >= 'A' && symbol <= 'Z' || symbol == '+' || symbol == '-'
					|| symbol >= '0' && symbol <= '9' || symbol == '.' || symbol == '%') {
					buffer[indexBuffer] = symbol;
					++indexBuffer;
					stage = first;
				}
				stage = first;
				isNeedAddLast = false;
			}
			break;
		}
	}
	if (isNeedAddLast) {
		strcat(result, buffer);
	}
	fclose(file);
	return result;
}