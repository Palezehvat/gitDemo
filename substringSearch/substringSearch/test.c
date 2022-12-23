#include "test.h"
#include "KMP.h"

bool test() {
	int errorCode = 0;
	bool itIsOK = findIndexSubstring("error", "ror", &errorCode) == 2;
	if (errorCode != 0 || !itIsOK) {
		return false;
	}
	itIsOK = findIndexSubstring("error", "a", &errorCode) == -1;
	if (errorCode != 0 || !itIsOK) {
		return false;
	}
	return findIndexSubstring("error", "rortutuut", &errorCode) == -1 && errorCode == 0;
}