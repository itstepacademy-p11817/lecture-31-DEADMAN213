#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <inttypes.h>
#include <stdlib.h>

uint8_t inputValue(const char* str) {
	uint8_t val = 0;

	printf(str);
	scanf("%hhu", &val);

	return val;
}

int8_t** createTable(const uint8_t rows, const uint8_t colls) {
	int8_t** table = (int8_t**)calloc(rows, sizeof(int8_t*));
	for (uint8_t i = 0; i < rows; i++) {
		*(table + i) = (int8_t*)calloc(colls, sizeof(int8_t));
	}

	return table;
}

int8_t** initTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			if (rand() % 2 == 0) {
				*(*(table + i) + j) = rand() % 10;
			}
			else {
				*(*(table + i) + j) = -rand() % 10;
			}
		}
	}

	return table;
}

int8_t** printTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			printf("%4hhi", *(*(table + i) + j));
		}
		putchar('\n');
	}

	return table;
}

int8_t** deleteTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		free(*(table + i));
	}
	free(table);

	return NULL;
}

int8_t** deleteLine(int8_t** table, uint8_t* rows, const uint8_t pos) {
	free(*(table + pos));
	for (uint8_t i = pos; i < *rows - 1; i++) {
		*(table + i) = *(table + i + 1);
	}

	return (int8_t**)realloc(table, --*rows * sizeof(int8_t*));
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create table.\n");
	printf("2 - Print table.\n");
	printf("3 - Dell zero lines.\n");
	printf("4 - Delete table.\n");
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

	int8_t** table = NULL;
	uint8_t row = 0;
	uint8_t coll = 0;

	bool flag = true;

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			if (table) {
				table = deleteTable(table, row, coll);
			}

			row = inputValue("Input num of a rows: ");
			coll = inputValue("Input num of a colls: ");

			table = createTable(row, coll);
			initTable(table, row, coll);

			break;

		case 2:
			if (table) {
				printf("Table:\n");
				printTable(table, row, coll);
			}
			else {
				printf("Table is empty.\n");
			}

			break;

		case 3:
			for (uint8_t i = 0; i < row; flag ? i : i++) {
				flag = false;
				for (uint8_t j = 0; j < coll; j++) {
					if (table[i][j] == 0) {
						table = deleteLine(table, &row, i);
						flag = true;
						break;
					}
				}
			}
			break;

		case 4:
			if (table) {
				table = deleteTable(table, row, coll);
				row = 0;
				coll = 0;
			}
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}

		printf("Press any key.\n");
		_getch();
	}

	if (table) {
		table = deleteTable(table, row, coll);
	}

	return 0;
}