#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Функция принимает файл с матрицей и создает сначала файл graph.dot, а затем создает graph.png, в том же каталоге что и программа.
bool workWithFiles(char* nameFileFrom) {
	FILE* file = fopen(nameFileFrom, "r");
	if (file == NULL) {
		return -1;
	}
	char symbol = 0;
	int matrix[50][50] = { 0 };
	int indexString = 0;
	int indexColumn = 0;
	int number = 0;
	int sizeMatrix = 0;
	while (fscanf(file, "%c", &symbol) == 1) {
		if (symbol == ' ') {
			matrix[indexString][indexColumn] = number;
			number = 0;
			indexColumn += 1;
		}
		else if (symbol == '\n') {
			matrix[indexString][indexColumn] = number;
			number = 0;
			sizeMatrix = indexColumn + 1;
			indexString += 1;
			indexColumn = 0;
		}
		else {
			if (number == 0) {
				number += symbol - '0';
			}
			else {
				number = number * 10 + symbol - '0';
			}
		}
	}
	fclose(file);
	matrix[indexString][indexColumn] = number;
	FILE* fileNew = fopen("graph.dot", "w");
	if (fileNew == NULL) {
		return -1;
	}
	fprintf(fileNew, "%s\n", "graph {");
	for (int i = 0; i < sizeMatrix; ++i) {
		for (int j = 0; j < sizeMatrix; ++j) {
			if (matrix[i][j] != 0) {
				fprintf(fileNew, "%d -- %d [label = \"%d\"];\n", i, j, matrix[i][j]);
			}
		}
	}
	fprintf(fileNew, "%s", "}");
	fclose(fileNew);
	system("dot -Tpng graph.dot -o graph.png");
	return true;
}

int main() {
	printf("Enter the name of the matrix file. No more than 99 symbols\n");
	char nameFileFrom[100] = { '\0' };
	int checkScanf = scanf("%s", nameFileFrom);
	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}
		checkScanf = scanf("%s", nameFileFrom);
	}
	workWithFiles(nameFileFrom);
}