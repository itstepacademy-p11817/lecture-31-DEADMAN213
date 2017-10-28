#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

char** inputNames(uint8_t* ln) {
	char buf[15] = "";
	char** lines = NULL;

	printf("Input student last name or empty line for exit: ");
	while (gets(buf) && buf[0] != '\0') {
		lines = (char**)realloc(lines, ++*ln * sizeof(char*));
		*(lines + *ln - 1) = (char*)calloc(strlen(buf) + 1, sizeof(char));
		strcpy(*(lines + *ln - 1), buf);
		printf("Input student last name or empty line for exit: ");
	}

	return lines;
}

char** printNames(char** lines, uint8_t ln) {
	printf("\nStudent`s last names: \n");
	for (uint8_t i = 0; i < ln; i++) {
		printf("%s.\n", *(lines + i));
	}

	return lines;
}

char** sortNames(char** lines, uint8_t ln) {
	char* box = NULL;
	for (uint8_t i = 0; i < ln - 1; i++) {
		for (uint8_t j = i + 1; j < ln; j++) {
			if (strcmp(*(lines + i), *(lines + j)) == 1) {
				box = *(lines + i);
				*(lines + i) = *(lines + j);
				*(lines + j) = box;
			}
		}
	}

	return lines;
}

char** deleteNames(char** lines, uint8_t ln) {
	for (uint8_t i = 0; i < ln; i++) {
		free(*(lines + i));
	}
	free(lines);

	return NULL;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create list.\n");
	printf("2 - Print list.\n");
	printf("3 - Sort list.\n");
	printf("4 - Delete list.\n");
	printf("5 - Exit.\n");
	printf("Choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	uint8_t ch = 0;
	uint8_t ln = 0;
	uint8_t** lines = NULL;
	
	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			pass();
			if (lines) {
				lines = deleteNames(lines, ln);
			}
			lines = inputNames(&ln);
			break;

		case 2:
			if (lines) {
				printNames(lines, ln);
			}
			else {
				printf("List is empty.\n");
			}
			break;

		case 3:
			if (lines) {
				sortNames(lines, ln);
			}
			else {
				printf("List is empty.\n");
			}
			break;

		case 4:
			lines = deleteNames(lines, ln);
			ln = 0;
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}

		printf("Press any key.\n");
		_getch();
	}

	return 0;
}