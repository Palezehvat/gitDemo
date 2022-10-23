#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>

bool converterToPostfixForm(char buffer[], char arrayOutput[]) {
	size_t sizeBuffer = strlen(buffer);
	char arrayOutput[100] = { '\0' };
	Stack* operatorActions = createStack();
	size_t i = 0;
	int notCountPriority = 0;
	while (i < sizeBuffer) {
		if (buffer[i] == '(') {
			notCountPriority += 1;
		}
		if (buffer[i] == ')') {
			notCountPriority -= 1;
			if (notCountPriority < 0) {
				return false;
			}
		}
		while (buffer[i] >= '0' && buffer[i] <= '9') {
			arrayOutput[i] = buffer[i];
			++i;
		}
		if (buffer[i] == '*' || buffer[i] == '+' || buffer[i] == '/' || buffer[i] == '-') {
			if (operatorActions == NULL) {
				push(operatorActions, buffer[i]);
			} else if (notCountPriority > 0) {
				push(operatorActions, buffer[i]);
			} else if (notCountPriority == 0){

			}
		}
	}
}

bool firstTest() {
	char buffer[12] = { '(', '1', ' ', '+', ' ', '2', ')', ' ', '*', ' ', '2', '\0' };
	char arrayOutput[100] = { '\0' };
	if (converterToPostfixForm(buffer, arrayOutput)) {
		return false;
	}
	int i = 0;
	char bufferNew[6] = { '1', '2', '+', '2', '*', '\0'};
	size_t sizearrayOutput = strlen(arrayOutput);
	for (int i = 0; i < sizearrayOutput; ++i) {
		if (i >= 6 || bufferNew[i] != arrayOutput[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	Stack* stack = createStack();
}