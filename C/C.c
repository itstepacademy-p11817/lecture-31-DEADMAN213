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

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create tables.\n");
	printf("2 - Print tables.\n");
	printf("3 - Multiply tabless.\n");
	printf("4 - Delete tables.\n");
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

	int8_t** A = NULL;
	uint8_t rowA = 0;
	uint8_t collA = 0;

	int8_t** B = NULL;
	uint8_t rowB = 0;
	uint8_t collB = 0;

	int8_t** C = NULL;
	uint8_t rowC = 0;
	uint8_t collC = 0;

	while ((ch = menu()) != 5) {
		switch (ch) {
		case 1:
			if (A) {
				A = deleteTable(A, rowA, collA);
			}
			if (B) {
				B = deleteTable(B, rowB, collB);
			}
			if (C) {
				C = deleteTable(C, rowC, collC);
			}

			rowA = inputValue("Input num of a rows for A: ");
			collA = inputValue("Input num of a colls for A: ");

			rowB = collA;
			collB = inputValue("Input num of a colls for B: ");

			rowC = 0;
			collC = 0;

			A = createTable(rowA, collA);
			B = createTable(rowB, collB);
			initTable(A, rowA, collA);
			initTable(B, rowB, collB);

			break;

		case 2:
			if (A) {
				printf("Table A:\n");
				printTable(A, rowA, collA);
			}
			else {
				printf("Table is empty.\n");
			}

			if (B) {
				printf("\nTable B:\n");
				printTable(B, rowB, collB);
			}
			else {
				printf("Table is empty.\n");
			}

			if (C) {
				printf("\nTable C:\n");
				printTable(C, rowC, collC);
			}

			break;

		case 3:
			for (uint8_t i = 0; i < rowA; i++) {
				C = (int8_t**)realloc(C, ++rowC * sizeof(int8_t*));
				*(C + i) = NULL;
				for (uint8_t j = 0; j < collB; j++) {
					*(C + i) = (int8_t*)realloc(*(C + i), (j + 1) * sizeof(int8_t));
					C[i][j] = 0;
					for (uint8_t k = 0; k < collA; k++) {
						C[i][j] += A[i][k] * B[k][j];
					}
				}
			}
			collC = collB;
			break;

		case 4:
			if (A) {
				A = deleteTable(A, rowA, collA);
				rowA = 0;
				collA = 0;
			}
			if (B) {
				B = deleteTable(B, rowB, collB);
				rowB = 0;
				collB = 0;
			}
			if (C) {
				C = deleteTable(C, rowC, collC);
				rowC = 0;
				collC = 0;
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

	if (A) {
		A = deleteTable(A, rowA, rowA);
	}
	if (B) {
		B = deleteTable(B, rowB, rowB);
	}
	if (C) {
		C = deleteTable(C, rowC, rowC);
	}

	return 0;
}