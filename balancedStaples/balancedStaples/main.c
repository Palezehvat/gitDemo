#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

bool isBalanced(char stringStaples[]) {

}

bool firstTest(void) {
	char stringStaples[5] = { '{', '}', '(', ')', '\0'};
	return isBalanced(stringStaples) == false;
}

bool secondTest(void) {
	char stringStaples[5] = { '{', '(', ')', '}', '\0'};
	return isBalanced(stringStaples) == true;
}

int main() {

}