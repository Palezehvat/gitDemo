#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <locale.h>
#include <stdbool.h>

int scanOne();

int whichPosition(int size, int step) {
	List* list = createList();
	addPositions(list, size);
	return counting(&list, size, step);
}

bool test1(void) {
	return whichPosition(5, 3) == 3;
}

bool test2(void) {
	return whichPosition(1, 3) == 0;
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (test1() && test2()) {
		printf("����� ������ �������!\n");
	} else {
		printf("������...");
		return -1;
	}
	printf("������� ����������� �����\n");
	int size = scanOne();
	if (size == 0) {
		return 0;
	}
	printf("������� ��� ����������\n");
	int step = scanOne();
	int result = whichPosition(size, step);
	if (result == -1) {
		printf("������...");
		return -1;
	} else {
		printf("%s %d", "������� ���� �� ����, ���������� ������� � �������� ������, ����� ���������� ����������� ������� ������� ���������� �� ���������. ����������� �������: ", result);
	}
}

int scanOne() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("������...\n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}