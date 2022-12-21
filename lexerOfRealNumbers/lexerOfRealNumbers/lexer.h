#pragma once

#include <stdbool.h>

typedef enum State {
	startZero,
	first,
	second,
	third,
	fourth,
	fifth
} State;

//Checking whether the string is a real number or not
bool isTheSequenceANumber(const char* string);