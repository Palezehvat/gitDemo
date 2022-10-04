#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include < string.h >
#include <stdbool.h>

int scanOneInt();
void addRecord(char number[], char name[], char listOfString[100][100], int records);
bool isStringEqual(char string1[], char string2[]);
void findNumberByName(char name[], char data[]);
void findNameByNumber(char number[], char data[]);
void saveInformation(char listOfStrings[100][100], int records);
void printRecords(char arrayOut[100][100]);

bool testAddRecord(char arrayOut[100][100]) {
	int records = 0;
	char name1[5] = { 'I','l','y','a', '\0'};
	char number1[12] = {'8','8','0','0','3','5','5','3','5','3','5','\0'};
	addRecord(number1, name1, arrayOut, records);
	saveInformation(arrayOut, records);
	records += 2;
	char name2[5] = { 'T', 'i', 'm', 'a', '\0'};
	char number2[12] = { '8','9','0','9','5','9','0','3','0','1','6','\0'};
	addRecord(number2, name2, arrayOut, records);
	if (!isStringEqual(arrayOut[0], name1)) {
		return false;
	}
	if (!isStringEqual(arrayOut[1], number1)) {
		return false;
	}
	if (!isStringEqual(arrayOut[2], name2)) {
		return false;
	}
	if (!isStringEqual(arrayOut[3], number2)) {
		return false;
	}
	return true;
}

bool testFindNumberByName() {
	char data[100] = { '\0' };
	char name[5] = { 'I','l','y','a', '\0' };
	char number[12] = { '8','8','0','0','3','5','5','3','5','3','5','\0' };
	
	findNumberByName(name, data);
	return isStringEqual(data, number);
}

bool testFindNameByNumber() {
	char data[100] = { '\0' };
	char name[5] = { 'I','l','y','a', '\0' };
	char number[12] = { '8','8','0','0','3','5','5','3','5','3','5','\0' };

	findNameByNumber(number, data);
	return isStringEqual(data, name);
}

bool testSaveInformation(char arrayOut[100][100]) {
	saveInformation(arrayOut, 4);
	FILE* file = fopen("listOfNumbersAndNames.txt", "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return;
	}
	char data[100] = { '\0' };
	int i = 0;
	while (fscanf(file, "%s", data) == 1)
	{
		if (i == 0 && !isStringEqual(data, "Ilya")) {
			return false;
		}
		if (i == 1 && !isStringEqual(data, "88003553535")) {
			return false;
		}
		if (i == 2 && !isStringEqual(data, "Tima")) {
			return false;
		}
		if (i == 3 && !isStringEqual(data, "89095903016")) {
			return false;
		}
		++i;
	}

	fclose(file);
	return true;
}

bool testPrint(char arrayOut[100][100]) {
	char data[100][100] = { '0' };
	printRecords(data);
	for (int i = 0; i < 4; ++i) {
		if (!isStringEqual(data[i], arrayOut[i])) {
			return false;
		}
	}
	return true;
}

bool isStringEqual(char string1[], char string2[]) {
	const size_t lengthString1 = strlen(string1);
	const size_t lengthString2 = strlen(string2);
	size_t i = 0;
	while (i < lengthString1 && i < lengthString2) {
		if (string1[i] != string2[i]) {
			return false;
		}
		++i;
	}
	return lengthString1 - lengthString2 == 0;
}

void addRecord(char number[], char name[], char listOfString[100][100], int records) {
	const size_t lengthName = strlen(name);
	for (size_t i = 0; i < lengthName; ++i) {
		listOfString[records][i] = name[i];
	}
	++records;
	const size_t lengthNumber = strlen(number);
	for (size_t i = 0; i < lengthNumber; ++i) {
		listOfString[records][i] = number[i];
	}
}

void printRecords(char arrayOut[100][100]) {
	FILE *file = fopen("listOfNumbersAndNames.txt", "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return;
	}
	char data[100] = { '\0' };
	int i = 0;
	while (fscanf(file, "%s", data) == 1)
	{
		size_t sizeData = strlen(data);
		for (size_t j = 0; j < sizeData; ++j) {
			arrayOut[i][j] = data[j];
		}
		++i;
	}

	fclose(file);
}

void findNumberByName(char name[], char data[]) {
	FILE* file = fopen("listOfNumbersAndNames.txt", "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return;
	}
	bool isNeedPrint = false;
	while (fscanf(file, "%s", data) == 1)
	{
		if (isNeedPrint) {
			return data;
			break;
		}

		if (isStringEqual(data, name)) {
			isNeedPrint = true;
		}
	}
	
	fclose(file);
}

void findNameByNumber(char number[],char last[]) {
	FILE* file = fopen("listOfNumbersAndNames.txt", "r");
	if (file == NULL) {
		printf("Файл не найден!");
		return;
	}
	char data[100] = { '\0' };
	while (fscanf(file, "%s", data) == 1)
	{
		if (isStringEqual(data, number)) {
			return last;
			break;
		}

		const size_t lengthLast = strlen(last);
		for (size_t i = 0; i < lengthLast; ++i) {
			last[i] = '\0';
		}

		const size_t lengthData = strlen(data);
		for (size_t i = 0; i < lengthData; ++i) {
			last[i] = data[i];
		}

	}

	fclose(file);
}

void saveInformation(char listOfStrings[100][100], int records) {
	FILE* file = fopen("listOfNumbersAndNames.txt", "a");
	if (file == NULL) {
		printf("Файл не найден!");
		return;
	}
	int i = 0;
	while (i < records) {
		fprintf(file, "%s\n", listOfStrings[i]);
		++i;
		fprintf(file, "%s\n", listOfStrings[i]);
		++i;
	}

	fclose(file);
}

void talkWithUser() {
	printf("%s", "Введите команду.0 - выйти, 1 - добавить запись(имя и телефон), 2 - распечатать все имеющиеся записи, 3 - найти телефон по имени, 4 - найти имя по телефону, 5 - сохранить текущие данные в файл \n");
	
	int comand = scanOneInt();
	
	while (comand < 0 || comand > 5) {
		printf("%s\n", "Такие команды отсутствуют.Повторите попытку");
		comand = scanOneInt();
	}

	char listOfString[100][100] = { '\0' };
	int records = 0;
	char data[100] = { '\0' };

	while (comand != 0) {
		if (comand == 1 && records < 100) {
			printf("%s\n", "Введите имя, а затем номер. Размер имени и номера должен быть меньше 100 символов");
			char name[100] = { '\0' };
			int checkScanf = scanf("%s", &name);
			while (checkScanf != 1 || (int)strlen(name) >= 100) {
				while (getchar() != '\n') {
				}

				printf("%s", "Ошибка... Проверьте правильность ввода \n");
				checkScanf = scanf("%s", &name);
			}
			char number[100] = { '\0' };
			checkScanf = scanf("%s", &number);
			while (checkScanf != 1 || (int)strlen(number) >= 100) {
				while (getchar() != '\n') {
				}

				printf("%s", "Ошибка... Проверьте правильность ввода \n");
				checkScanf = scanf("%s", &number);
			}
			addRecord(number, name, listOfString, records);
			records += 2;
		} else if (comand == 1) {
			printf("%s", "Вы ввели слишком много записей\n");
		}
		if (comand == 2) {
			char arrayOut[100][100] = {'\0'};
			printRecords(arrayOut);
			int i = 0;
			while (i < 100 && strlen(arrayOut[i])){
				size_t sizeArrayOut = strlen(arrayOut[i]);
				for (int j = 0; j < sizeArrayOut; ++j) {
					printf("%c", arrayOut[i][j]);
				}
				++i;
				printf("\n");
			}
		}
		if (comand == 3) {
			printf("%s\n", "Введите имя. Размер имени должен быть меньше 100 символов");
			char name[100] = {'\0'};
			int checkScanf = scanf("%s", &name);
			while (checkScanf != 1 || (int)strlen(name) >= 100) {
				while (getchar() != '\n') {
				}

				printf("%s", "Ошибка... Проверьте правильность ввода \n");
				checkScanf = scanf("%s", &name);
			}

			findNumberByName(name, data);
			printf("%s", data);
			for (int i = 0; i < 100; ++i) {
				data[i] = '\0';
 			}
		}
		if (comand == 4) {
			printf("%s\n", "Введите номер.");
			char number[100] = { '\0' };
			int checkScanf = scanf("%s", &number);
			while (checkScanf != 1 || (int)strlen(number) >= 100) {
				while (getchar() != '\n') {
				}

				printf("%s", "Ошибка... Проверьте правильность ввода \n");
				checkScanf = scanf("%s", &number);
			}
			findNameByNumber(number, data);
			printf("%s", data);
			for (int i = 0; i < 100; ++i) {
				data[i] = '\0';
			}
		}
		if (comand == 5) {
			saveInformation(listOfString, records);
		}
		printf("%s\n", "Введите последующую команду.(0 - если хотите выйти)");
		comand = scanOneInt();
		while (comand < 0 || comand > 5) {
			printf("%s\n", "Такие команды отсутствуют.Повторите попытку");
			comand = scanOneInt();
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	char arrayOut[100][100] = { '\0' };
	printf("%s", "Нужны ли вам тесты? Если да то введите 1, однако при тестах в файл будут записаны тестовые значения и вам придётся самостоятельно их убрать\n");
	int isNeedTests = scanOneInt();
	if (isNeedTests == 1) {
		if (testAddRecord(arrayOut) && testSaveInformation(arrayOut) && testFindNameByNumber(arrayOut) && testFindNumberByName(arrayOut) && testPrint(arrayOut)) {
			printf("%s", "Тесты успешно пройдены!\n");
		}
		else {
			printf("%s", "Тесты не пройдены...");
			return 0;
		}
	}
	talkWithUser();
}

int scanOneInt() {
	int number = 0;
	int checkScanf = scanf("%d", &number);

	while (checkScanf != 1) {
		while (getchar() != '\n') {
		}

		printf("%s", "Ошибка... Проверьте правильность ввода \n");
		checkScanf = scanf("%d", &number);
	}

	return number;
}