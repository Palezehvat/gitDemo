#include "test.h"
#include "lexerOfComments.h"

bool test() {
    Error errorCheck = ok;
    char* stringForCheck = "/*fdfdfdfd*//**//*dfsdfsff*/";
    char* result = lexerOfComments("table.txt", "test.txt", &errorCheck);
    return errorCheck == ok && strcmp(result, stringForCheck) == 0;
}