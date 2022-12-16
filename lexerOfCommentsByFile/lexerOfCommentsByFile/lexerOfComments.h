#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef enum Error {
	ok,
	fileProblem
}Error;

char* lexerOfComments(const char* fileName);