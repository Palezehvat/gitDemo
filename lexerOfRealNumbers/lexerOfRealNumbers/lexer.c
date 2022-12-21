#include "lexer.h"
#include <ctype.h>
#include <string.h>

bool isTheSequenceANumber(const char* string) {
    size_t sizeString = strlen(string);
    State state = startZero;
    for (size_t i = 0; i < sizeString + 1; ++i) {
        switch (state)
        {
        case startZero:
            if (i == 0 && i + 1 == sizeString) {
                return false;
            }
            if (isdigit(string[i])) {
                state = first;
                break;
            }
            return false;
        case first:
            if (i == sizeString) {
                return true;
            }
            if (isdigit(string[i])) {
                state = first;
                break;
            }
            else if (string[i] == '.') {
                state = second;
                if (i + 1 == sizeString) {
                    return false;
                }
                break;
            }
            else if (string[i] == 'E') {
                state = fourth;
                if (i + 1 == sizeString) {
                    return false;
                }
                break;
            }
            return false;
        case second:
            if (i == sizeString) {
                return true;
            }
            if (isdigit(string[i])) {
                state = third;
                break;
            }
            return false;
        case third:
            if (i == sizeString) {
                return true;
            }
            if (string[i] == 'E') {
                state = fourth;
                if (i + 1 == sizeString) {
                    return false;
                }
                break;
            }
            else if (isdigit(string[i])) {
                state = third;
                break;
            }
            return false;
        case fourth:
            if (i == sizeString) {
                return true;
            }
            if (isdigit(string[i])) {
                state = fifth;
                break;
            }
            else if (string[i] == '+' || string[i] == '-') {
                state = fifth;
                if (i + 1 == sizeString) {
                    return false;
                }
                break;
            }
            return false;
        case fifth:
            if (i == sizeString) {
                return true;
            }
            if (isdigit(string[i])) {
                state = fifth;
                break;
            }
            return false;
        }
    }
        return true;
}