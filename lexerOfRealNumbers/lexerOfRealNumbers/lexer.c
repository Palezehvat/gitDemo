#include "lexer.h"
#include <ctype.h>
#include <string.h>

bool isTheSequenceANumber(const char* string) {
	size_t sizeString = strlen(string);
	int state = 0;
	for (size_t i = 0; i < sizeString; ++i) {
		switch (state)
		{
		case(0):
			if (isdigit(string[i])) {
				state = 1;
				break;
			}
			return false;
		case(1):
			if (isdigit(string[i])) {
				state = 1;
				break;
			} else if (string[i] == '.') {
				state = 2;
				break;
			} else if (string[i] == 'E') {
				state = 3;
				break;
			}
			return false;
		case(2):
			if (string[i] == 'E' && string[i-1] != '.') {
				state = 3;
				break;
			} else if (isdigit(string[i])) {
				state = 2;
				break;
			}
			return false;
		case(3):
			if (isdigit(string[i])) {
				state = 4;
				break;
			} else if (string[i] == '+' || string[i] == '-') {
				state = 4;
				break;
			}
			return false;
		case(4):
			if (isdigit(string[i])) {
				state = 4;
				break;
			}
			return false;
		}
		
	}
	return string != NULL && string[sizeString - 1] != '+' && string[sizeString - 1] != '-' && string[sizeString - 1] != 'E';
}