#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int scanOne();



void talkWithUser() {
	printf("%s", "Введите команду.0 - выйти, 1 - добавить запись(имя и телефон), 2 - распечатать все имеющиеся записи, 3 - найти телефон по имени, 4 - найти имя по телефону, 5 - сохранить текущие данные в файл \n");
	
	int comand = scanOne();
	
	while (comand < 0 || comand > 5) {
		printf("%s\n", "Такие команды отсутствуют.Повторите попытку");
		comand = scanOne();
	}

	while (comand != 0) {
		
		printf("%s\n", "Введите последующую команду.(0 - если хотите выйти)");
		comand = scanOne();
		while (comand < 0 || comand > 5) {
			printf("%s\n", "Такие команды отсутствуют.Повторите попытку");
			comand = scanOne();
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	talkWithUser();
}

int scanOne() {
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