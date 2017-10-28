#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>

uint8_t initValue(const char* str) {
	uint8_t val = 0;

	printf(str);
	scanf("%hhu", &val);

	return val;
}

uint8_t** createTable(const uint8_t rows, const uint8_t colls) {
	uint8_t** table = (uint8_t**)calloc(rows, sizeof(uint8_t*));
	for (uint8_t i = 0; i < rows; i++) {
		*(table + i) = (uint8_t*)calloc(colls, sizeof(uint8_t));
	}

	return table;
}

uint8_t* initLine(uint8_t* line, const uint8_t colls) {
	for (uint8_t i = 0; i < colls; i++) {
		*(line + i) = rand() % 100;
	}

	return line;
}

uint8_t** initTable(uint8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		*(table + i) = initLine(*(table + i), colls);
	}

	return table;
}

uint8_t** printTable(uint8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			printf("%4hhu", *(*(table + i) + j));
		}
		putchar('\n');
	}

	return table;
}

uint8_t** deleteTable(uint8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		free(*(table + i));
	}
	free(table);

	return NULL;
}

uint8_t** addLine(uint8_t** table, uint8_t* rows, const uint8_t colls, const uint8_t pos) {
	table = (uint8_t**)realloc(table, ++*rows * sizeof(uint8_t*));
	for (uint8_t i = (*rows) - 1; i > pos - 1; i--) {
		*(table + i) = *(table + i - 1);
	}
	*(table + pos - 1) = (uint8_t*)calloc(colls, sizeof(uint8_t));
	*(table + pos - 1) = initLine(*(table + pos - 1), colls);

	return table;
}

uint8_t** deleteLine(uint8_t** table, uint8_t* rows, const uint8_t pos) {
	free(*(table + pos - 1));
	for (uint8_t i = pos - 1; i < *rows - 1; i++) {
		*(table + i) = *(table + i + 1);
	}

	return (uint8_t**)realloc(table, --*rows * sizeof(uint8_t*));
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create table.\n");
	printf("2 - Print table.\n");
	printf("3 - Add line to the end.\n");
	printf("4 - Add line to the start.\n");
	printf("5 - Add line at the position.\n");
	printf("6 - Delete line at the position.\n");
	printf("7 - Delete table.\n");
	printf("8 - Exit.\n");
	printf("Choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

int main(void) {
	srand(time(NULL));

	uint8_t ch = 0;
	uint8_t pos = 0;
	uint8_t rows = 0;
	uint8_t colls = 0;

	uint8_t** table = NULL;

	while ((ch = menu()) != 8) {
		switch (ch) {
		case 1:
			if (table) {
				deleteTable(table, rows, colls);
			}
			rows = initValue("Input rows: ");
			colls = initValue("Input colls: ");
			table = createTable(rows, colls);
			initTable(table, rows, colls);
			break;

		case 2:
			if (table) {
				printTable(table, rows, colls);
			}
			break;

		case 3:
			table = addLine(table, &rows, colls, rows + 1);
			break;

		case 4:
			table = addLine(table, &rows, colls, 1);
			break;

		case 5:
			pos = initValue("Input position: ");
			table = addLine(table, &rows, colls, pos);
			break;

		case 6:
			pos = initValue("Input position: ");
			table = deleteLine(table, &rows, pos);
			break;

		case 7:
			table = deleteTable(table, rows, colls);
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