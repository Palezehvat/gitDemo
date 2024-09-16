#include "avlTree.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

int scanOne();

bool talkWithUser(void) {
	printf("� ��� ���� ��������� �������:\n0 - ����� �� �������������� ����\n1 - �������� �������� �� ��������� ����� � �������. ���� ����� ���� ��� ����, �������� ���������� �� �����.\n2 - �������� �������� �� ��������� ����� �� �������.���� ������ ����� ���, ������������ NULL.\n3 - ��������� ������� ��������� �����.\n4- ������� �������� ���� � ��������� � ��� �������� �� �������.���� ������ ����� ���, ������� ������ �� ������.\n");
	int command = scanOne();

	while (command > 4 || command < 0) {
		printf("�� ����� �������������� �������. ���������� ��� ���!\n");
		command = scanOne();
	}

	Tree* tree = createTree();
	char* stringCopy = NULL;

	while (command != 0) {
		printf("������� ����. �� ������, ��� 100 ��������\n");
		char key[100] = { '\0' };
		int checkScanfKey = scanf("%s", key);
		while (checkScanfKey != 1) {
			while (getchar() != '\n') {
			}
			printf("������...\n");
			checkScanfKey = scanf("%s", key);
		}

		switch (command) {
		case 1:
			printf("������� ������ ������. �� �� ������ ��������� 100 ��������, � ����� ������� ������\n");
			int size = scanOne();
			while (size < 0 || size > 100) {
				while (getchar() != '\n') {
				}
				printf("������...\n");
				size = scanOne();
			}
			char buffer[101] = { '\0' };
			int checkScanf = scanf("%s", buffer);

			while (checkScanf != 1) {
				while (getchar() != '\n') {
				}
				printf("������...\n");
				checkScanf = scanf("%s", buffer);
			}
			size_t sizeBuffer = strlen(buffer);
			char* string = calloc(sizeBuffer + 1, sizeof(char));
			if (string == NULL) {
				return false;
			}
			for (size_t i = 0; i < sizeBuffer; ++i) {
				string[i] = buffer[i];
			}
			addToTree(tree, key, string);
			break;
		case 2:
			stringCopy = returnValueByKey(tree, key);
			if (string != NULL) {
				printf("%s\n", string);
			}
			break;
		case 3:
			if (isKeyInTree(tree, key)) {
				printf("��, ����� ���� �������!\n");
			}
			else {
				printf("���, ������ ����� ���!\n");
			}
			break;
		case 4:
			deleteNodeInTreeByKey(tree, key);
			break;
		}
		printf("������� ��������� �������!\n");
		command = scanOne();

		while (command > 4 || command < 0) {
			printf("�� ����� �������������� �������. ���������� ��� ���!\n");
			command = scanOne();
		}
	}

	clearTree(tree);
}

int main() {
	setlocale(LC_ALL, "RUS");
	if (testForAvlTree()) {
		printf("����� ������ �������!\n");
	}
	else {
		printf("������...\n");
		return -1;
	}
	
	if (!talkWithUser()) {
		printf("������...\n");
		return -1;
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