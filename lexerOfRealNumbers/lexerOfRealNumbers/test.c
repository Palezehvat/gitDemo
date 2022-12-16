#include "test.h"
#include "lexer.h"

bool test() {
	return isTheSequenceANumber("1E4") && !isTheSequenceANumber("1.E4") && isTheSequenceANumber("1.2E4")
		&& isTheSequenceANumber("1.4") && isTheSequenceANumber("1.4E+45") && !isTheSequenceANumber("1.4E-")
		&& isTheSequenceANumber("14E-2") && isTheSequenceANumber("14");
}