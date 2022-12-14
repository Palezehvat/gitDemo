#include "test.h"
#include "list.h"

bool test() {
	Error errorCheck = ok;
	FILE* file = fopen("test.txt", "r");
	if (file == NULL) {
		errorCheck = anotherError;
		return false;
	}
	List* list = createList(&errorCheck);
	if (list == NULL) {
		errorCheck = emptyPointer;
		return false;
	}
	char buffer[100] = { '\0' };
	while (fscanf(file, "%s", buffer) == 1) {
		addToList(list, buffer, &errorCheck);
		if (errorCheck != ok) {
			clearList(list, &errorCheck);
			return false;
		}
	}
	addWithASymbolStrings(list, &errorCheck);
	if (errorCheck != ok) {
		clearList(list, &errorCheck);
		return false;
	}
	bool result = isLastElementSame(list, "adad", &errorCheck);
	if (errorCheck != ok) {
		clearList(list, &errorCheck);
		return false;
	}
	clearList(list, &errorCheck);
	return result;
}