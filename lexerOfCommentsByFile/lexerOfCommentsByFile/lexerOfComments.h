#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Error {
	ok,
	fileProblem
}Error;

char* lexerOfComments(const char* fileNameTable, const char* fileNameWithStrings, Error* errorCheck);