#pragma once

#include <stdio.h>

//Variable for error checking
typedef enum Error {
	ok,
	errorWithFile,
	anotherError
} Error;

//return string with emails
char* workWithFileAndReturnString(const char* nameFile, Error* errorCheck);